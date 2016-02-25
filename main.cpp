#include <QCoreApplication>
#include <stdlib.h>
#include <stdio.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_OUTLINE_H
#include <freetype/tttables.h>

#include "hb.h"
#include "hb-ft.h"

int main(int argc, char *argv[])
{
        char *pFile = "ArialArabic.ttf";

        FT_Library ft_library;
        Q_ASSERT(!FT_Init_FreeType(&ft_library));

        FT_Face ft_face;
        Q_ASSERT(!FT_New_Face(ft_library,pFile, 0, &ft_face));

        hb_buffer_t *buffer = hb_buffer_create();

        // arabic
        char *language = "ar";

        hb_buffer_set_direction(buffer, HB_DIRECTION_RTL); /* or LTR */
        hb_buffer_set_script(buffer, HB_SCRIPT_ARABIC); /* see hb-unicode.h */
        hb_buffer_set_language(buffer, hb_language_from_string(language, strlen(language)));

        //wchar_t wch[] = { 0x644,0x627,0 };
        wchar_t wch[] = { 0x634,0x20,0x634,0x634,0 };

        const QString str(QString::fromWCharArray(wch));
        QByteArray bytes = str.toUtf8();
        const char *pt = bytes.data();

        /* Layout the text */
        hb_buffer_add_utf8(buffer,pt, strlen(pt), 0, strlen(pt));

        hb_font_t *font = hb_ft_font_create(ft_face, NULL);
        hb_shape(font, buffer, NULL, 0);

        unsigned int         glyph_count;
        hb_glyph_info_t     *glyph_info   = hb_buffer_get_glyph_infos(buffer, &glyph_count);

        hb_codepoint_t cp = -1;

        for (unsigned j = 0; j < glyph_count; ++j) {
            cp = glyph_info[j].codepoint;
        }

        hb_buffer_clear_contents(buffer);

        hb_buffer_destroy(buffer);
        hb_font_destroy(font);

        FT_Done_FreeType(ft_library);

        return 0;
}
