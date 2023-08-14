#include <optional>
#include "token.hpp"

namespace dsp {

struct keyword {

inline static constexpr std::optional<enum token::type_t>
find(const std::string_view s)
{
  if (s.length() == 0) { return {}; }

  std::string_view::size_type ix = 0;

  switch (s[ix++]) {
  case 'A': [[fallthrough]];
  case 'a':
    if (ix < s.length()) {
      switch (s[ix++]) {
      case 'L': [[fallthrough]];
      case 'l':
        if (ix < s.length()) {
          switch (s[ix++]) {
          case 'H': [[fallthrough]];
          case 'h':
            if (ix == s.length()) return { token::type_t::_alh };
            break;
          case 'L': [[fallthrough]];
          case 'l':
            if (ix == s.length()) return { token::type_t::_all };
            break;
          case 'U': [[fallthrough]];
          case 'u':
            if (ix == s.length()) return { token::type_t::_alu };
            break;
          }
        }
        break;
      case 'N': [[fallthrough]];
      case 'n':
        if (ix < s.length()) {
          switch (s[ix++]) {
          case 'D': [[fallthrough]];
          case 'd':
            if (ix == s.length()) return { token::type_t::_and };
            break;
          }
        }
        break;
      case 'D': [[fallthrough]];
      case 'd':
        if (ix < s.length()) {
          switch (s[ix++]) {
          case 'D': [[fallthrough]];
          case 'd':
            if (ix == s.length()) return { token::type_t::_add };
            break;
          case '2':
            if (ix == s.length()) return { token::type_t::_ad2 };
            break;
          }
        }
        break;
      }
    }
    break;
  case 'M': [[fallthrough]];
  case 'm':
    if (ix < s.length()) {
      switch (s[ix++]) {
      case '0':
        if (ix == s.length()) return { token::type_t::_m0 };
        break;
      case '1':
        if (ix == s.length()) return { token::type_t::_m1 };
        break;
      case '2':
        if (ix == s.length()) return { token::type_t::_m2 };
        break;
      case '3':
        if (ix == s.length()) return { token::type_t::_m3 };
        break;
      case 'C': [[fallthrough]];
      case 'c':
        if (ix < s.length()) {
          switch (s[ix++]) {
          case '0':
            if (ix == s.length()) return { token::type_t::_mc0 };
            break;
          case '1':
            if (ix == s.length()) return { token::type_t::_mc1 };
            break;
          case '2':
            if (ix == s.length()) return { token::type_t::_mc2 };
            break;
          case '3':
            if (ix == s.length()) return { token::type_t::_mc3 };
            break;
          }
        }
        break;
      case 'U': [[fallthrough]];
      case 'u':
        if (ix < s.length()) {
          switch (s[ix++]) {
          case 'L': [[fallthrough]];
          case 'l':
            if (ix == s.length()) return { token::type_t::_mul };
            break;
          }
        }
        break;
      case 'O': [[fallthrough]];
      case 'o':
        if (ix < s.length()) {
          switch (s[ix++]) {
          case 'V': [[fallthrough]];
          case 'v':
            if (ix == s.length()) return { token::type_t::_mov };
            break;
          }
        }
        break;
      case 'V': [[fallthrough]];
      case 'v':
        if (ix < s.length()) {
          switch (s[ix++]) {
          case 'I': [[fallthrough]];
          case 'i':
            if (ix == s.length()) return { token::type_t::_mvi };
            break;
          }
        }
        break;
      }
    }
    break;
  case 'N': [[fallthrough]];
  case 'n':
    if (ix < s.length()) {
      switch (s[ix++]) {
      case 'O': [[fallthrough]];
      case 'o':
        if (ix < s.length()) {
          switch (s[ix++]) {
          case 'P': [[fallthrough]];
          case 'p':
            if (ix == s.length()) return { token::type_t::_nop };
            break;
          }
        }
        break;
      }
    }
    break;
  case 'O': [[fallthrough]];
  case 'o':
    if (ix < s.length()) {
      switch (s[ix++]) {
      case 'R': [[fallthrough]];
      case 'r':
        if (ix == s.length()) return { token::type_t::_or };
        else {
          switch (s[ix++]) {
          case 'G': [[fallthrough]];
          case 'g':
            if (ix == s.length()) return { token::type_t::_org };
            break;
          }
        }
        break;
      }
    }
    break;
  case 'X': [[fallthrough]];
  case 'x':
    if (ix < s.length()) {
      switch (s[ix++]) {
      case 'O': [[fallthrough]];
      case 'o':
        if (ix < s.length()) {
          switch (s[ix++]) {
          case 'R': [[fallthrough]];
          case 'r':
            if (ix == s.length()) return { token::type_t::_xor };
            break;
          }
        }
        break;
      }
    }
    break;
  case 'S': [[fallthrough]];
  case 's':
    if (ix < s.length()) {
      switch (s[ix++]) {
      case 'U': [[fallthrough]];
      case 'u':
        if (ix < s.length()) {
          switch (s[ix++]) {
          case 'B': [[fallthrough]];
          case 'b':
            if (ix == s.length()) return { token::type_t::_sub };
            break;
          }
        }
        break;
      case 'R': [[fallthrough]];
      case 'r':
        if (ix == s.length()) return { token::type_t::_sr };
        break;
      case 'L': [[fallthrough]];
      case 'l':
        if (ix == s.length()) return { token::type_t::_sl };
        break;
      }
    }
    break;
  case 'R': [[fallthrough]];
  case 'r':
    if (ix < s.length()) {
      switch (s[ix++]) {
      case 'R': [[fallthrough]];
      case 'r':
        if (ix == s.length()) return { token::type_t::_rr };
        break;
      case 'L': [[fallthrough]];
      case 'l':
        if (ix == s.length()) return { token::type_t::_rl };
        else {
          switch (s[ix++]) {
          case '8':
            if (ix == s.length()) return { token::type_t::_rl8 };
            break;
          }
        }
        break;
      }
    }
    break;
  case 'C': [[fallthrough]];
  case 'c':
    if (ix < s.length()) {
      switch (s[ix++]) {
      case 'L': [[fallthrough]];
      case 'l':
        if (ix < s.length()) {
          switch (s[ix++]) {
          case 'R': [[fallthrough]];
          case 'r':
            if (ix == s.length()) return { token::type_t::_clr };
            break;
          }
        }
        break;
      }
    }
    break;
  case 'D': [[fallthrough]];
  case 'd':
    if (ix < s.length()) {
      switch (s[ix++]) {
      case 'M': [[fallthrough]];
      case 'm':
        if (ix < s.length()) {
          switch (s[ix++]) {
          case 'A': [[fallthrough]];
          case 'a':
            if (ix == s.length()) return { token::type_t::_dma };
            else {
              switch (s[ix++]) {
              case 'H': [[fallthrough]];
              case 'h':
                if (ix == s.length()) return { token::type_t::_dmah };
                break;
              }
            }
            break;
          }
        }
        break;
      }
    }
    break;
  case 'J': [[fallthrough]];
  case 'j':
    if (ix < s.length()) {
      switch (s[ix++]) {
      case 'M': [[fallthrough]];
      case 'm':
        if (ix < s.length()) {
          switch (s[ix++]) {
          case 'P': [[fallthrough]];
          case 'p':
            if (ix == s.length()) return { token::type_t::_jmp };
            break;
          }
        }
        break;
      }
    }
    break;
  case 'B': [[fallthrough]];
  case 'b':
    if (ix < s.length()) {
      switch (s[ix++]) {
      case 'T': [[fallthrough]];
      case 't':
        if (ix < s.length()) {
          switch (s[ix++]) {
          case 'M': [[fallthrough]];
          case 'm':
            if (ix == s.length()) return { token::type_t::_btm };
            break;
          }
        }
        break;
      }
    }
    break;
  case 'L': [[fallthrough]];
  case 'l':
    if (ix < s.length()) {
      switch (s[ix++]) {
      case 'P': [[fallthrough]];
      case 'p':
        if (ix < s.length()) {
          switch (s[ix++]) {
          case 'S': [[fallthrough]];
          case 's':
            if (ix == s.length()) return { token::type_t::_lps };
            break;
          }
        }
        break;
      }
    }
    break;
  case 'E': [[fallthrough]];
  case 'e':
    if (ix < s.length()) {
      switch (s[ix++]) {
      case 'N': [[fallthrough]];
      case 'n':
        if (ix < s.length()) {
          switch (s[ix++]) {
          case 'D': [[fallthrough]];
          case 'd':
            if (ix == s.length()) return { token::type_t::_end };
            else {
              switch (s[ix++]) {
              case 'I': [[fallthrough]];
              case 'i':
                if (ix == s.length()) return { token::type_t::_endi };
                break;
              case 'S': [[fallthrough]];
              case 's':
                if (ix == s.length()) return { token::type_t::_ends };
                break;
              }
            }
            break;
          }
        }
        break;
      case 'Q': [[fallthrough]];
      case 'q':
        if (ix < s.length()) {
          switch (s[ix++]) {
          case 'U': [[fallthrough]];
          case 'u':
            if (ix == s.length()) return { token::type_t::_equ };
            break;
          }
        }
        break;
      }
    }
    break;
  }
  return {};
}

};

}
