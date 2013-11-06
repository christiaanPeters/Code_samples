#include <stdio.h>
#include <stdbool.h>

#include "stdtypes.h"
#include "resource_detector.h"
#include "unzip.h"

#define TEMP_BUF_SIZE       2050  /* size of temporary buffer during unzipping                          */
#define HEX_CHARS_PER_LINE  10    /* number of hexadecimal characters per line (in unzip_dump_hex())    */
#define HISTORY_SIZE        1024

static BYTE history[HISTORY_SIZE];
static int start;
static int end;

static void history_init(void)
/* pre:  true
 * post: 'start' en 'end' staan op 0,
 *       zodat 'history[]' is geinitialiseerd
 */
{
	start = 0;
	end = 0;
}

static void history_put(BYTE c)
/* pre : 0 <= 'start'< HISTORY_SIZE
 0 <= 'end'  < HISTORY_SIZE
 'start' geeft aan waar met lezen gestart kan worden en
 'end' geeft aan waar het laatste byte geplaatst is.
 Dus start, start+1, ... end-1 bevatten bytes die al geplaatst zijn
 post: byte 'c' op positie 'end' van array 'history[]' geschreven
 'end' opgehoogd, maar als vervolgens geldt:
 Als 'end' == HISTORY_SIZE dan 'end' = 0
 Als 'end' == 'start' dan 'start' ophogen
 Als 'start' == HISTORY_SIZE dan 'start' = 0
 */
{

	history[end] = c;
	end++;

	if (start == HISTORY_SIZE)
		start = 0;
	if (end == HISTORY_SIZE)
		end = 0;
	if (end == start)
		start++;

}

static BYTE history_get(int i)
/* pre:  true
 * post: return de byte uit 'history[]' die staat op een offset 'i'
 *       ten opzichte van 'start'
 */
{
	int index = start + i;
	return history[index];
}

extern void history_test(void)
/* pre:  true
 * post: een test is uitgevoerd die aantoont dat de history module goed werkt
 */
{
	/*
	 * TODO (II)
	 */
	history_init();

	history_put('a');
	history_put('b');
	history_put('c');
	history_put('d');
	history_put('e');
	history_put('f');
	history_put('g');

	printf("history_put test: \n");
	for (int x = 0; x < 7; x++)
		printf("%i", history[x]);

	printf("history_get test: \n");
	for (int i = 0; i < HISTORY_SIZE; i++)
		printf("%i, ", history_get(0));
}

extern bool unzip_dump_hex(const char * filename_in, const char * filename_out)
/* pre:  'filename_in' is de naam van een bestaand, gecomprimeerd bestand
 *       'filename_out' is een nul-terminated string
 * post: 'filename_out' is de naam van een tekstbestand waarin alle bytes
 *       van 'filename_in' zijn weergegeven als 2 hexadecimale symbolen
 *       elke regel bevat een adres en 10 bytes.
 *       'filename_out' bevat dus een hexadecimale dump van alle bytes
 *       van 'filename_in'
 */
{
	FILE * file_in;
	FILE * file_out;
	BYTE b;
	int i = 0;
	int j = 0;

	file_in = fopen(&filename_in, "rb");
	file_out = fopen(&filename_out, "wb");

	if (file_in == 0 || file_out == 0)	//check to make sure the files are open.
		return false;

	while (fread(&b, sizeof(b), 1, file_in) != 0) {
		fprintf(file_out, "%i: ", i);
		i++;
		while (fread(&b, sizeof(b), 1, file_in) != 0 && j < 10) {
			fprintf(file_out, "%x ", b);
			j++;
		}
		fprintf(file_out, "\n");
		j = 0;

		fclose(file_in);
		fclose(file_out);
		return true;
	}

}

extern bool unzip_dump_header_and_text(const char * filename_in,
		const char * filename_out)
/* pre:  'filename_in' is de naam van een bestaand, gecomprimeerd bestand
 *       'filename_out' is een nul-terminated string
 * post: 'filename_out' is de naam van een tekstbestand waarin de inhoud
 *       van 'filename_in' als volgt is weergegeven:
 *       bij een header van type 1: 2 getallen (positie & lengte)
 *       bij een header van type 0: alle karakters die behoren bij deze header
 */
{
	FILE * file_in;
	FILE * file_out;
	USHORT header;
	USHORT header_type;
	USHORT header_length;
	USHORT header_position;
	BYTE b;
	int i;

	file_in = fopen(&filename_in, "rb");
	file_out = fopen(&filename_out, "wb");

	if (file_in == 0 || file_out == 0)	//check to make sure the files are open.
		return false;

	while (fread(&header, sizeof(USHORT), 1, file_in)) {
		header_type = (header >> 15) & 0x01;
		header_length = (header) & 0x1f;
		header_position = (header >> 5) & 0x3ff;

		if (header_type == 0) {
			for (int i = 0; i < header; i++) {
				fread(&b, sizeof(BYTE), 1, file_in);
				fwrite(&b, sizeof(BYTE), 1, file_out);
			}
		} else if (header_type == 1) {
			fprintf(file_out, "[%i,%i]", header_position, header_length);
		}
	}

	fclose(file_in);
	fclose(file_out);
	return true;
}

extern bool unzip_lz77(const char * filename_in, const char * filename_out)
/* pre:  'filename_in' is de naam van een bestaand, gecomprimeerd bestand
 *       'filename_out' is een nul-terminated string
 * post: als de files niet geopend kunnen worden
 *          return false
 *       anders
 *          file 'filename_out' is aangemaakt bestaande uit de
 *          LZ77 omzetting van het bestand 'filename_in'
 *          return true
 */
{
	FILE * file_in;
	FILE * file_out;
	USHORT header;
	USHORT header_type;
	USHORT header_length;
	USHORT header_position;
	BYTE temp_buf[TEMP_BUF_SIZE];
	BYTE b;
	int h = 0;

	/*
	 * TODO (V)
	 */

	file_in = fopen(&filename_in, "rb");
	file_out = fopen(&filename_out, "wb");

	if (file_in == 0 || file_out == 0)	//check to make sure the files are open.
		return false;

	while (fread(&header, sizeof(USHORT), 1, file_in)) {
		header_type = (header >> 15) & 0x01;
		header_length = (header) & 0x1f;
		header_position = (header >> 5) & 0x3ff;

		if (header_type == 0) {
			for (int i = 0; i < header; i++) {
				if (i < 2048) {
					fread(&b, sizeof(BYTE), 1, file_in);
					fwrite(&b, sizeof(BYTE), 1, file_out);
					temp_buf[i] = b;
				}
				h = header;
			}
		} else if (header_type == 1) {
			for (int i = 0; i < header_length; i++) {
				b = history_get(header_position + i);
				fprintf(file_out, "%c", b);
				temp_buf[i] = b;
			}
			h = header_length;
		}

		for (int i = 0; i < h; i++) {
			history_put(temp_buf[i]);
		}
	}

	fclose(file_in);
	fclose(file_out);
	return true;
}

