#include "SDL2/SDL_pixels.h"
#include "Terminal.hpp"
#include <any>
#include <iostream>
#include <string>
#include <system_error>
#include <vector>

void Terminal::SetGlyph(int x, int y, TerminalGlyph g) {
  auto glyph = &buffer[y * width + x];
  glyph->character = g.character;
  glyph->fg = g.fg;
  glyph->bg = g.bg;
}

int Terminal::Print(int x, int y, const std::wstring &text) {
  if (y >= height || y < 0 || x >= width || x + (int)text.size() < 0)
    return 0;

  std::vector<TerminalGlyph> formatted = std::vector<TerminalGlyph>();

  SDL_Color fg = {255, 255, 255, 255};
  SDL_Color bg = {0, 0, 0, 255};

  for (int i = 0; i < (int)text.size(); i++) {
    int charcode = text[i];
    if (charcode == L'[') {
      int iterator = i + 1;
      if (text[iterator] == '[') {
        auto glyph = (TerminalGlyph){charcode, fg, bg};
        formatted.push_back(glyph);
        break;
      }

      for (; iterator < (int)text.size(); iterator++) {
        if (text[iterator] == 'f' || text[iterator] == 'b') {
          SDL_Color *defaultCol = nullptr;
          SDL_Color *col = nullptr;
          if (text[iterator] == 'f') {
            col = &fg;
            defaultCol = &defaultForegroundColor;
          } else if (text[iterator] == 'b') {
            col = &bg;
            defaultCol = &defaultBackgroundColor;
          }
          if (col == nullptr)
            break;
          iterator++;

          std::wstring r = L"", g = L"", b = L"", a = L"";

          if (text[iterator] == 'd') {
            col->r = defaultCol->r;
            col->g = defaultCol->g;
            col->b = defaultCol->b;
            col->a = defaultCol->a;
            if (text[++iterator] == ']') {
              i = iterator;
              break;
            }
          }

          if (text[iterator] == ',') {
            r = L"0";
          } else {
            for (; text[iterator] != ','; iterator++) {
              r.append(text.substr(iterator, 1));
            }
          }
          iterator++;

          if (text[iterator] == ',') {
            g = L"0";
          } else {
            for (; text[iterator] != ','; iterator++) {
              g.append(text.substr(iterator, 1));
            }
          }
          iterator++;

          if (text[iterator] == ',') {
            b = L"0";
          } else {
            for (; text[iterator] != ','; iterator++) {
              b.append(text.substr(iterator, 1));
            }
          }

          iterator++;
          if (text[iterator] == ']') {
            a = L"255";
          } else {
            for (; text[iterator] != ']'; iterator++) {
              a.append(text.substr(iterator, 1));
            }
          }

          col->r = stoi(r);
          col->g = stoi(g);
          col->b = stoi(b);
          col->a = stoi(a);
          i = iterator;
          break;
        }
      }

    } else {
      auto glyph = (TerminalGlyph){charcode, fg, bg};
      formatted.push_back(glyph);
    }
  }

  for (int i = 0; i < (int)formatted.size(); i++) {
    SetGlyph(x + i, y, formatted[i]);
  }
  return formatted.size();
}
