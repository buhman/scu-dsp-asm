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

M0-M3 must not appear in in DMA source/destination arguments
------------------------------------------------------------

For example, the following are not legal:

.. code::
   
   DMA D0,M0,#$02
   DMA M1,D0,#$02

Instead, they should be written as:

.. code::
   
   DMA D0,MC0,#$02
   DMA MC1,D0,#$02
   
``dspasm.exe`` generates the same code given either the former or
latter example as input. scu-dsp-asm, however, rejects the former
example as invalid: it misleads what the result of the operation is.

This change is not consistent with what is written in the SCU manual
(ST-97-R5-072694).

Differences that affect code generation
=======================================

Spurious invalid X-bus opcode generation
----------------------------------------

Under seemingly-random circumstances, ``dspasm.exe`` emits the
undefined X-bus opcode ``001``. Given:

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

Misleading, contradictory, and completely incorrect documentation
=================================================================

DMA default "add mode"
----------------------

Contrast to what is written in the SCU manual (ST-97-R5-072694), the
default DMA "add mode" for both dspasm.exe and scp-dsp-asm is
``2``. E.g:

- ``DMA`` is a synonym for ``DMA2``
  
- ``DMAH`` is a synonym for ``DMAH2``

In "Sega Developers Conference Conference Proceedings March 5-7, 1996"
pdf page 48, printed page 3-14, slide 25:

   You need to modify your object code, either by hand or with a
   custom tool.

This is completely incorrect, and both scu-dsp-asm and dspasm.exe will
emit "add mode 1" via the ``DMA1`` and ``DMAH1`` mnemonics.

DMA "add mode" and bytes
------------------------

All of the documentation you have read is invalid; here is the correct
relationship between DMA "add mode" mnemonics, and the number of
incremented bytes:

.. list-table::
   :header-rows: 1
   :stub-columns: 1

   * - mnemonic
     - D0 → [RAM]
     - [RAM] →D0
   * - DMA0
     - 0 bytes
     - 0 bytes
   * - DMA1
     - 0 bytes
     - 2 bytes
   * - DMA2
     - 4 bytes
     - 4 bytes
   * - DMA4
     - 4 bytes
     - 8 bytes
   * - DMA8
     - 0 bytes
     - 16 bytes
   * - DMA16
     - 0 bytes
     - 32 bytes
   * - DMA32
     - 4 bytes
     - 64 bytes
   * - DMA64
     - 4 bytes
     - 128 bytes
