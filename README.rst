###########
scu-dsp-asm
###########

scu-dsp-asm is an assembler for SCU DSP mnemonics, using SEGA syntax.

Usage:

.. code::
   
   scu-dsp-asm input-file.asm output-file.bin

If no arguments are given, scu-dsp-asm starts a basic REPL.

Wherever possible, scu-dsp-asm attempts to preserve compatibility with
the same source code used with the SEGA-authored ``dspasm.exe``,
**except** in the cases where ``dspasm.exe`` behavior is considered a
bug.

Current status
==============

100% of the documented dspasm.exe features are supported, as well as
miscellaneous undocumented features.

scu-dsp-asm correctly assembles all of the examples in the test/
directory in this repository, with caveats listed below.

scp-dsp-asm has not been tested exhaustively, and the test programs do
not cover 100% of the possible SCU DSP instructions or arguments.

Differences that affect source code
===================================

MC0-MC3 must not appear in in DMA source/destination arguments
--------------------------------------------------------------

For example, the following are not legal:

.. code::
   
   DMA D0,MC0,#$02
   DMA MC1,D0,#$02

Instead, they should be written as:

.. code::
   
   DMA D0,M0,#$02
   DMA M1,D0,#$02
   
``dspasm.exe`` generates the same code given either the former or
latter example as input. scu-dsp-asm, however, rejects the former
example as invalid: it misleads what the result of the operation is.

This change is consistent with what is written in the SCU manual
(ST-97-R5-072694), but is inconsistent with SEGA's SCU DSP examples.

Differences that affect code generation
=======================================

DMA default "add mode"
----------------------

``dspasm.exe`` has a bug where, despite the SCU manual
(ST-97-R5-072694) claiming that the default DMA "add mode" is ``1``,
the generated code is add mode ``2``.

This bug is documented in "Sega Developers Conference Conference
Proceedings March 5 7, 1996" on pdf page 48, printed page 3-14,
slide 25. However, Sega of America did not fully understand the nature
of the bug: patching ``dspasm.exe`` output is not necessary, because
``dspasm.exe`` does in fact generate the correct code for the ``DMA1``
mnemonic.

In short:

- ``dspasm.exe`` assembles ``DMA`` as the equivalent of the ``DMA2``
  mnemonic

- scu-dsp-asm assembles ``DMA`` as the equivalent of the ``DMA1``
  mnemonic, which is the correct behavior as originally intended by
  SEGA.

Spurious invalid X-bus opcodes generation
-----------------------------------------

Under seemly-random circumstances, ``dspasm.exe`` emits the undefined
X-bus opcode ``001``. Given:

.. code::
   
   MOV M3,A  MOV 1,PL

The ``dspasm.exe``-generated code is:

.. code::
   
   00000000100001101101010100000001
           ^ 
However, the correct code should be:

.. code::
   
   00000000000001101101010100000001
           ^

This is particularly interesting because the example mnemonics did not
contain any X-bus operation to start with.
	   
Motorola S-record output is not supported
-----------------------------------------

Instead, scu-dsp-asm currently emits a raw binary file that contains
fully assembled SCU DSP code.
