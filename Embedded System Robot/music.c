#include "open_interface.h"
#include "music.h"

/// Load three songs onto the iRobot
/**
 * Before calling this method, be sure to initialize the open interface by calling:
 *
 *   oi_t* sensor = oi_alloc();
 *   oi_init(sensor); 
 *
 */
void load_songs() {

	// Notes: oi_load_song takes four arguments
	// arg1 - an integer from 0 to 16 identifying this song
	// arg2 - an integer that indicates the number of notes in the song (if greater than 16, it will consume the next song index's storage space)
	// arg3 - an array of integers representing the midi note values (example: 60 = C, 61 = C sharp)
	// arg4 - an array of integers representing the duration of each note (in 1/64ths of a second)
	// 
	// For a note sheet, see page 12 of the iRobot Creat Open Interface datasheet

//	unsigned int rickrollNumNotes = 11;
//	unsigned char rickrollNotes[11]    = {53, 55, 48, 55, 57, 60, 58, 57, 53, 55, 48};
//	unsigned char rickrollDuration[11] = {48, 64, 16, 48, 48, 8,  8,  8,  48, 64, 64};
////	oi_loadSong(RICK_ROLL, rickrollNumNotes, rickrollNotes, rickrollDuration);
//
//	unsigned int ImperialMarchNumNotes = 19;
//	unsigned char ImperialMarchNotes[19]     = {55, 55, 55, 51, 58, 55, 51, 58, 55, 0,  62, 62, 62, 63, 58, 54, 51, 58, 55};
//	unsigned char ImperialMarchDurations[19] = {32, 32, 32, 20, 12, 32, 20, 12, 32, 32, 32, 32, 32, 20, 12, 32, 20, 12, 32};
////	oi_loadSong(IMERPIAL_MARCH, ImperialMarchNumNotes, ImperialMarchNotes, ImperialMarchDurations);
//
//	unsigned int mario1NumNotes = 49;
//	unsigned char mario1Notes[49]    = {48, 60, 45, 57, 46, 58,  0, 48, 60, 45, 57, 46, 58,  0, 41, 53, 38, 50, 39, 51,  0, 41, 53, 38, 50, 39, 51,  0, 51, 50, 49, 48, 51, 50, 44, 43, 49, 48, 54, 53, 52, 58, 57, 56, 51, 47, 46, 45, 44 };
//	unsigned char mario1Duration[49] = {12, 12, 12, 12, 12, 12, 62, 12, 12, 12, 12, 12, 12, 62, 12, 12, 12, 12, 12, 12, 62, 12, 12, 12, 12, 12, 12, 48,  8,  8,  8, 24, 24, 24, 24, 24, 24,  8,  8,  8,  8,  8,  8, 16, 16, 16, 16, 16, 16 };
////	oi_loadSong(MARIO_UNDERWORLD, mario1NumNotes, mario1Notes, mario1Duration);
//
//	unsigned int mario2NumNotes = 65;
//	unsigned char mario2Notes[65]    = {50, 52, 54, 55, 57, 58, 59, 59, 59, 59, 59, 55, 64, 63, 64, 0, 55, 57, 59, 60, 62, 64, 63, 65, 64,  0, 55, 62, 61, 62,  0, 55, 57, 59, 60, 61, 62, 55, 65, 64,  0, 55, 67, 67, 67, 67, 69,  0, 67, 65, 65, 65, 65, 67,  0, 65, 64, 57, 59, 65, 64, 64, 64, 59, 60 };
//	unsigned char mario2Duration[65] = {18, 18, 18, 18, 18, 18,  9,  9, 18, 18, 45,  9, 54, 54, 54, 9,  9,  9,  9,  9,  9, 54, 36, 18, 54, 45,  9, 54, 54, 54,  9,  9,  9,  9,  9,  9, 54, 36, 18, 54, 45,  9, 54, 54, 54, 18, 18,  9,  9, 54, 54, 54, 18, 18,  9,  9, 54, 18, 18, 18,  9,  9, 27,  9, 54 };
////	oi_loadSong(MARIO_UNDERWATER, mario2NumNotes, mario2Notes, mario2Duration);

	//6 parts 15 notes per part
	unsigned int starWarsNumNotesp1 = 15;
	unsigned char starWarsNotesp1[15] = {50, 50, 50, 55, 62, 60, 59, 57, 67, 62, 60, 59, 57, 67, 62};
	unsigned char starWarsDurationp1[15] = {21, 21, 21, 128, 128, 21, 21, 21, 128, 64, 21, 21, 21, 128, 64};
	oi_loadSong(STAR_WARS_P1, starWarsNumNotesp1, starWarsNotesp1, starWarsDurationp1);


	unsigned int starWarsNumNotesp2 = 15;
	unsigned char starWarsNotesp2[15] = {60, 59, 60, 57, 50, 50, 55, 62, 60, 59, 57, 67, 62, 60, 59};
	unsigned char starWarsDurationp2[15] = {21, 21, 21, 128, 64, 32, 128, 128, 21, 21, 21, 128, 64, 21, 21};
	oi_loadSong(STAR_WARS_P2, starWarsNumNotesp2, starWarsNotesp2, starWarsDurationp2);

	unsigned int starWarsNumNotesp3 = 15;
	unsigned char starWarsNotesp3[15] = {57, 67, 62, 60, 59, 60, 57, 50, 50, 52, 52, 60, 59, 57, 55};
	unsigned char starWarsDurationp3[15] = {21, 128, 64, 21, 21, 21, 128, 64, 32, 96, 32, 32, 32, 32, 32};
	oi_loadSong(STAR_WARS_P3, starWarsNumNotesp3, starWarsNotesp3, starWarsDurationp3);

    unsigned int starWarsNumNotesp4 = 15;
    unsigned char starWarsNotesp4[15] = {55, 57, 59, 57, 52, 54, 50, 50, 52, 52, 60, 59, 57, 55, 62};
    unsigned char starWarsDurationp4[15] = {21, 21, 21, 64, 32, 64, 64, 32, 96, 32, 32, 32, 32, 32, 48};
    oi_loadSong(STAR_WARS_P4, starWarsNumNotesp4, starWarsNotesp4, starWarsDurationp4);

    unsigned int starWarsNumNotesp5 = 15;
    unsigned char starWarsNotesp5[15] = {57, 57, 50, 50, 52, 52, 60, 59, 57, 55, 55, 57, 59, 57, 52};
    unsigned char starWarsDurationp5[15] = {16, 128, 64, 32, 96, 32, 32, 32, 32, 32, 21, 21, 21, 64, 32};
    oi_loadSong(STAR_WARS_P5, starWarsNumNotesp5, starWarsNotesp5, starWarsDurationp5);

    unsigned int starWarsNumNotesp6 = 12;
    unsigned char starWarsNotesp6[12] = {54, 62, 62, 67, 65, 63, 62, 60, 58, 57, 55, 62};
    unsigned char starWarsDurationp6[12] = {64, 64, 32, 32, 32, 32, 32, 32, 32, 32, 32, 160};
    oi_loadSong(STAR_WARS_P6, starWarsNumNotesp6, starWarsNotesp6, starWarsDurationp6);

    unsigned int shootingSoundNumNotes = 3;
    unsigned char shootingSoundNotes[3] = {96, 96, 96};
    unsigned char shootingSoundDuration[3] = {8, 8, 8};
    oi_loadSong(GUN, shootingSoundNumNotes, shootingSoundNotes, shootingSoundDuration);




/**
* 128bpm = approx 2.1bps
32 measures per minute
each int = 1/64th second
half note = 128
dotted half = 160
quarter = 64
eigth = 32
dotted eigth = 48
triplet = 21 (21.3)
dotted quarter = 96
*/
}

void play_StarWars(){
    oi_play_song(0);
    timer_waitMillis(12955);
    oi_play_song(1);
    timer_waitMillis(13126);
    oi_play_song(2);
    timer_waitMillis(11814);
    oi_play_song(3);
    timer_waitMillis(9736);
    oi_play_song(4);
    timer_waitMillis(10236);
    oi_play_song(5);
    timer_waitMillis(9002);
}

void play_Gun(){
    oi_play_song(6);
    timer_waitMillis(450);
    oi_play_song(6);
    timer_waitMillis(450);

}
