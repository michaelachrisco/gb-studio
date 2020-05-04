// clang-format off
#pragma bank=3
// clang-format on

#include "UI.h"
#include "BankData.h"
#include "GameTime.h"
#include "Math.h"
#include "ASMHelpers.h"
#include "Input.h"
#include <string.h>

#define FRAME_CENTER_OFFSET 64

const unsigned char ui_frame_tl_tiles[1] = {0xC0};
const unsigned char ui_frame_bl_tiles[1] = {0xC6};
const unsigned char ui_frame_tr_tiles[1] = {0xC2};
const unsigned char ui_frame_br_tiles[1] = {0xC8};
const unsigned char ui_frame_t_tiles[1] = {0xC1};
const unsigned char ui_frame_b_tiles[1] = {0xC7};
const unsigned char ui_frame_l_tiles[1] = {0xC3};
const unsigned char ui_frame_r_tiles[1] = {0xC5};
const unsigned char ui_frame_bg_tiles[1] = {0xC4};
const unsigned char ui_colors[2][360] = {
    {0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA,
     0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA,
     0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA,
     0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA,
     0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA,
     0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA,
     0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA,
     0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA,
     0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA,
     0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA,
     0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA,
     0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA,
     0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA,
     0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA,
     0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA,
     0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA,
     0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA,
     0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA,
     0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA,
     0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA,
     0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA,
     0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA,
     0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA, 0xCA},
    {0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9,
     0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9,
     0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9,
     0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9,
     0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9,
     0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9,
     0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9,
     0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9,
     0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9,
     0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9,
     0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9,
     0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9,
     0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9,
     0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9,
     0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9,
     0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9,
     0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9,
     0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9,
     0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9,
     0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9,
     0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9,
     0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9,
     0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9, 0xC9}};
const unsigned char ui_white[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const unsigned char ui_black[16] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

void UIInit_b() {
  UBYTE *ptr;

  UISetPos(160, 144);

  // Load frame tiles from data bank
  ptr = (BankDataPtr(FRAME_BANK)) + FRAME_BANK_OFFSET;
  SetBankedBkgData(FRAME_BANK, 192, 9, ptr);

  set_bkg_data(0xC9, 1, ui_white);
  set_bkg_data(0xCA, 1, ui_black);

  ptr = (BankDataPtr(CURSOR_BANK)) + CURSOR_BANK_OFFSET;
  SetBankedBkgData(CURSOR_BANK, 0xCB, 1, ptr);
}

void UIUpdate_b() {
  UBYTE interval;

  if (win_speed == 5 && ((game_time & 0x7) != 0)) {
    return;
  } else if (win_speed == 4 && ((game_time & 0x3) != 0)) {
    return;
  } else if (win_speed == 3 && ((game_time & 0x1) != 0)) {
    return;
  }

  if (win_speed == 1) {
    interval = 2;
  } else {
    interval = 1;
  }

  if (win_pos_x != win_dest_pos_x) {
    if (win_pos_x < win_dest_pos_x) {
      win_pos_x += interval;
    } else {
      win_pos_x -= interval;
    }
  }

  if (win_pos_y != win_dest_pos_y) {
    if (win_pos_y < win_dest_pos_y) {
      win_pos_y += interval;
    } else {
      win_pos_y -= interval;
    }
  } else {
    UIDrawTextBuffer();
    // Reenable hide_sprites_under_win if
    // disabled, once UI has closed
    if (!hide_sprites_under_win && UIIsClosed()) {
      hide_sprites_under_win = TRUE;
    }
  }

  WX_REG = win_pos_x + 7;
  WY_REG = win_pos_y;
}

void UIDrawFrame_b(UBYTE x, UBYTE y, UBYTE width, UBYTE height) {
  UINT16 id = 0;
  UBYTE i, j;
  UBYTE k = 1;

  id = 0x9C00;  // Window VRAM

  SetTile(id, *ui_frame_tl_tiles);                                // Frame top left
  SetTile(id + ((height + 1) * 32), *ui_frame_bl_tiles);          // Frame bottom left
  SetTile(id + width, *ui_frame_tr_tiles);                        // Frame top right
  SetTile(id + ((height + 1) * 32) + width, *ui_frame_br_tiles);  // Frame bottom right

  for (j = 1; j != height + 1; j++) {
    SetTile(id + (j * 32), *ui_frame_l_tiles);          // Frame left
    SetTile(id + (j * 32) + width, *ui_frame_r_tiles);  // Frame right

    for (i = 1; i != width; ++i) {
      SetTile(id + (j * 32) + i, *ui_frame_bg_tiles);  // Frame background
    }
  }

  for (i = 1; i != width; ++i) {
    SetTile(id + i, *ui_frame_t_tiles);                        // Frame top
    SetTile(id + ((height + 1) * 32) + i, *ui_frame_b_tiles);  // Frame bottom
  }
}

void UIDrawDialogueFrame_b(UBYTE h) { UIDrawFrame_b(0, 0, 19, h); }

void UISetColor_b(UBYTE color) {
  UINT16 id = 0;
  UBYTE x, y;

  id = 0x9C00;  // Window VRAM

  // Not sure why need to set_bkg_data again but this doesn't
  // work in rom without reseting here
  set_bkg_data(0xC9, 1, ui_white);
  set_bkg_data(0xCA, 1, ui_black);
  for (y = 0; y != 18; y++) {
    for (x = 0; x != 20; x++) {
      SetTile(id + x + (y * 32), *ui_colors[color]);
    }
  }
}

void UIShowText_b() {
  UWORD var_index;
  UBYTE i, j, k;
  UBYTE value;
  unsigned char value_string[6];

  LOG("UIShowText 6\n");

  for (i = 1, k = 0; i < 81; i++) {
    LOG("LOOP TEXT %i %i (%c)\n", i, tmp_text_lines[i], tmp_text_lines[i]);
    // Replace variable references in text
    if (tmp_text_lines[i] == '$') {
      if (tmp_text_lines[i + 3] == '$') {
        var_index = (10 * (tmp_text_lines[i + 1] - '0')) + (tmp_text_lines[i + 2] - '0');
      } else if (tmp_text_lines[i + 4] == '$') {
        var_index = (100 * (tmp_text_lines[i + 1] - '0')) + (10 * (tmp_text_lines[i + 2] - '0')) +
                    (tmp_text_lines[i + 3] - '0');
      } else {
        text_lines[k] = tmp_text_lines[i];
        ++k;
        continue;
      }

      value = script_variables[var_index];
      j = 0;

      if (value == 0) {
        text_lines[k] = '0';
      } else {
        // itoa implementation
        while (value != 0) {
          value_string[j++] = '0' + (value % 10);
          value /= 10;
        }
        j--;
        while (j != 255) {
          text_lines[k] = value_string[j];
          k++;
          j--;
        }
        k--;
      }
      // Jump though input past variable placeholder
      if (var_index >= 100) {
        i += 4;
      } else {
        i += 3;
      }
    } else {
      text_lines[k] = tmp_text_lines[i];
    }
    ++k;
  }

  if (menu_layout) {
    text_num_lines = tmp_text_lines[0];
    UIDrawFrame(0, 0, 8, text_num_lines);
    UISetPos(MENU_LAYOUT_INITIAL_X, MENU_CLOSED_Y);
    UIMoveTo(MENU_LAYOUT_INITIAL_X, MENU_CLOSED_Y - ((text_num_lines + 2) << 3), text_in_speed);
  } else {
    LOG("tmp_text_lines = %u - %u - %u\n", tmp_text_lines[0], tmp_text_lines[1], tmp_text_lines[2]);
    text_num_lines = MIN(tmp_text_lines[0], 4);
    LOG("text_num_lines = %u \n", text_num_lines);
    UIDrawDialogueFrame(text_num_lines);
    UISetPos(0, MENU_CLOSED_Y);
    UIMoveTo(0, MENU_CLOSED_Y - ((text_num_lines + 2) << 3), text_in_speed);
  }

  LOG("UIShowText 100\n");

  text_drawn = FALSE;
  text_x = 0;
  text_y = 0;
  text_count = 0;
  text_tile_count = 0;

  LOG("UIShowText 101\n");
}

void UIDrawTextBufferChar_b() {
  UBYTE letter;
  UBYTE i, text_remaining, word_len;
  UBYTE text_size = strlen(text_lines);
  UBYTE tile;
  UBYTE *ptr;
  UINT16 id;

  if (text_wait > 0) {
    text_wait--;
    return;
  }

  if (text_count < text_size) {
    // win_speed = text_draw_speed;
    text_drawn = FALSE;

    if (text_count == 0) {
      text_x = 0;
      text_y = 0;
    }

    letter = text_lines[text_count] - 32;

    // Clear tile data ready for text
    ptr = BankDataPtr(FONT_BANK) + FONT_BANK_OFFSET;

    // Determine if text can fit on line
    text_remaining = 18 - text_x;
    word_len = 0;
    for (i = text_count; i != text_size; i++) {
      if (text_lines[i] == ' ' || text_lines[i] == '\n' || text_lines[i] == '\0') {
        break;
      }
      word_len++;
    }
    if (word_len > text_remaining && word_len < 18) {
      text_x = 0;
      text_y++;
    }

    if (text_lines[text_count] != '\b' && text_lines[text_count] != '\n') {
      i = text_tile_count + avatar_enabled * 4;

      SetBankedBkgData(FONT_BANK, TEXT_BUFFER_START + i, 1, ptr + ((UWORD)letter * 16));
      tile = TEXT_BUFFER_START + i;
      // set_win_tiles(
      //     text_x + 1 + avatar_enabled * 2 + menu_enabled + (text_y >= text_num_lines ? 9 : 0),
      //     (text_y % text_num_lines) + 1, 1, 1, &tile);
      id = 0x9C00 +
           MOD_32((text_x + 1 + avatar_enabled * 2 + menu_enabled +
                   (text_y >= text_num_lines ? 9 : 0))) +
           ((UINT16)MOD_32((text_y % text_num_lines) + 1) << 5);
      SetTile(id, tile);

      text_tile_count++;
    }

    if (text_lines[text_count] == '\b') {
      text_x--;
      text_wait = 10;
    }

    text_count++;
    text_x++;
    if (text_lines[text_count] == '\n') {
      text_x = 0;
      text_y++;
      text_count++;
    } else if (text_x > 17) {
      text_x = 0;
      text_y++;
    }

    if (text_draw_speed == 0) {
      UIDrawTextBufferChar_b();
    }
  } else {
    text_drawn = TRUE;
    // restore the user selected text draw speed as it
    // might have been override in UIShowMenu
    text_draw_speed = tmp_text_draw_speed;
  }
}

void UICloseDialogue_b() {
  UIMoveTo(menu_layout ? MENU_LAYOUT_INITIAL_X : 0, MENU_CLOSED_Y, text_out_speed);

  // Reset variables
  text_count = 0;
  text_lines[0] = '\0';
  text_tile_count = 0;
  text_num_lines = 3;
  menu_enabled = FALSE;
  menu_layout = 0;
  avatar_enabled = FALSE;
}

void UIOnInteract_b() {
  if (INPUT_A_PRESSED) {
    if (text_drawn && text_count != 0) {
      if (menu_enabled) {
        if (menu_cancel_on_last_option && menu_index + 1 == menu_num_options) {
          script_variables[menu_flag] = 0;
        } else {
          script_variables[menu_flag] = menu_index + 1;
        }
        UICloseDialogue_b();
      } else {
        UICloseDialogue_b();
      }
    }
  } else if (menu_enabled) {
    if (INPUT_UP_PRESSED) {
      menu_index = MAX(menu_index - 1, 0);
      UIDrawMenuCursor();
    } else if (INPUT_DOWN_PRESSED) {
      menu_index = MIN(menu_index + 1, menu_num_options - 1);
      UIDrawMenuCursor();
    } else if (INPUT_LEFT_PRESSED) {
      if (menu_layout == 0) {
        menu_index = MAX(menu_index - 4, 0);
      } else {
        menu_index = 0;
      }
      UIDrawMenuCursor();
    } else if (INPUT_RIGHT_PRESSED) {
      if (menu_layout == 0) {
        menu_index = MIN(menu_index + 4, menu_num_options - 1);
      } else {
        menu_index = menu_num_options - 1;
      }
      UIDrawMenuCursor();
    } else if (menu_cancel_on_b && INPUT_B_PRESSED) {
      script_variables[menu_flag] = 0;
      UICloseDialogue_b();
    }
  }
}
