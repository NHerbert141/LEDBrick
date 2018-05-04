#ifndef _FADE_STATUS_GAMMA_H
#define _FADE_STATUS_GAMMA_H

#if defined ( ESP8266 )
  #include <pgmspace.h>
#else
  #include <avr/pgmspace.h>
#endif

const flvar_t* const FadeStatusNoGamma = nullptr;

#if FADE_STATUS_PWM_BITS == 8
/* 101-step brightness table: gamma = 2.3 for 8-bit PWM*/ 
const flvar_t FadeStatusGammaTable[101] PROGMEM = {
	0, 1, 1, 1, 1, 2, 2, 2,
	3, 3, 4, 4, 5, 5, 6, 7,
	7, 8, 9, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 20, 21, 22, 24,
	25, 27, 28, 30, 31, 33, 35, 37,
	38, 40, 42, 44, 46, 49, 51, 53,
	55, 58, 60, 62, 65, 67, 70, 73,
	75, 78, 81, 84, 87, 90, 93, 96,
	99, 103, 106, 109, 113, 116, 120, 123,
	127, 131, 134, 138, 142, 146, 150, 154,
	158, 163, 167, 171, 176, 180, 185, 189,
	194, 199, 203, 208, 213, 218, 223, 228,
	234, 239, 244, 250, 255
};

#elif FADE_STATUS_PWM_BITS == 9
/* 101-step brightness table: gamma = 2.3 for 9-bit PWM*/ 
const flvar_t FadeStatusGammaTable[101] PROGMEM = {
	0, 1, 1, 1, 2, 2, 3, 3,
	4, 5, 6, 7, 8, 9, 10, 11,
	13, 14, 16, 17, 19, 21, 22, 24,
	26, 29, 31, 33, 36, 38, 41, 44,
	46, 49, 52, 56, 59, 62, 66, 69,
	73, 77, 80, 84, 89, 93, 97, 102,
	106, 111, 115, 120, 125, 130, 136, 141,
	147, 152, 158, 164, 170, 176, 182, 188,
	195, 201, 208, 215, 221, 229, 236, 243,
	250, 258, 266, 273, 281, 289, 298, 306,
	314, 323, 332, 340, 349, 358, 368, 377,
	387, 396, 406, 416, 426, 436, 446, 457,
	467, 478, 489, 500, 511
};

#elif FADE_STATUS_PWM_BITS == 10
/* 101-step brightness table: gamma = 2.3 for 10-bit PWM*/ 
const flvar_t FadeStatusGammaTable[101] PROGMEM = {
	0, 1, 1, 1, 2, 3, 4, 5,
	6, 7, 9, 10, 12, 14, 16, 19,
	21, 24, 26, 29, 33, 36, 39, 43,
	47, 51, 55, 60, 65, 70, 75, 80,
	85, 91, 97, 103, 110, 116, 123, 130,
	137, 145, 152, 160, 168, 177, 185, 194,
	203, 212, 222, 232, 242, 252, 262, 273,
	284, 295, 307, 318, 330, 342, 355, 368,
	380, 394, 407, 421, 435, 449, 463, 478,
	493, 508, 524, 540, 556, 572, 589, 606,
	623, 640, 658, 676, 694, 712, 731, 750,
	769, 789, 809, 829, 849, 870, 891, 912,
	934, 956, 978, 1000, 1023
};

#elif FADE_STATUS_PWM_BITS == 11
/* 101-step brightness table: gamma = 2.3 for 11-bit PWM*/ 
const flvar_t FadeStatusGammaTable[101] PROGMEM = {
	0, 1, 1, 2, 3, 4, 6, 8,
	10, 12, 15, 18, 21, 25, 29, 33,
	38, 43, 48, 54, 60, 67, 73, 81,
	88, 96, 105, 113, 123, 132, 142, 153,
	164, 175, 187, 199, 211, 224, 238, 252,
	266, 281, 296, 312, 328, 344, 362, 379,
	397, 416, 435, 454, 474, 495, 515, 537,
	559, 581, 604, 627, 651, 676, 701, 726,
	752, 779, 806, 833, 861, 890, 919, 948,
	979, 1009, 1040, 1072, 1104, 1137, 1171, 1205,
	1239, 1274, 1310, 1346, 1383, 1420, 1458, 1496,
	1535, 1574, 1615, 1655, 1696, 1738, 1781, 1824,
	1867, 1911, 1956, 2001, 2047
};

#elif FADE_STATUS_PWM_BITS == 12
/* 101-step brightness table: gamma = 2.3 for 12-bit PWM*/ 
const flvar_t FadeStatusGammaTable[101] PROGMEM = {
	0, 1, 2, 4, 6, 9, 12, 15,
	20, 24, 30, 36, 43, 50, 58, 66,
	76, 86, 97, 108, 120, 133, 147, 161,
	177, 193, 209, 227, 245, 265, 285, 306,
	327, 350, 373, 398, 423, 449, 476, 503,
	532, 562, 592, 624, 656, 689, 723, 758,
	795, 832, 870, 908, 948, 989, 1031, 1074,
	1118, 1163, 1208, 1255, 1303, 1352, 1402, 1453,
	1505, 1558, 1612, 1667, 1723, 1780, 1838, 1897,
	1958, 2019, 2081, 2145, 2209, 2275, 2342, 2410,
	2479, 2549, 2620, 2692, 2766, 2840, 2916, 2993,
	3071, 3150, 3230, 3311, 3394, 3477, 3562, 3648,
	3735, 3823, 3913, 4003, 4095
};

#elif FADE_STATUS_PWM_BITS == 13
/* 101-step brightness table: gamma = 2.3 for 13-bit PWM*/ 
const flvar_t FadeStatusGammaTable[101] PROGMEM = {
	0, 1, 3, 5, 8, 12, 18, 24,
	31, 40, 50, 61, 73, 87, 102, 118,
	136, 155, 176, 198, 221, 246, 273, 301,
	330, 361, 394, 428, 464, 502, 541, 582,
	625, 670, 716, 764, 813, 865, 918, 973,
	1030, 1089, 1149, 1212, 1276, 1342, 1410, 1480,
	1552, 1626, 1701, 1779, 1859, 1940, 2024, 2110,
	2197, 2287, 2379, 2473, 2568, 2666, 2766, 2868,
	2972, 3079, 3187, 3297, 3410, 3525, 3642, 3761,
	3882, 4005, 4131, 4259, 4389, 4521, 4655, 4792,
	4931, 5072, 5215, 5361, 5509, 5659, 5812, 5966,
	6123, 6283, 6445, 6609, 6775, 6944, 7115, 7288,
	7464, 7642, 7823, 8006, 8191
};

#elif FADE_STATUS_PWM_BITS == 14
/* 101-step brightness table: gamma = 2.3 for 14-bit PWM*/ 
const flvar_t FadeStatusGammaTable[101] PROGMEM = {
	0, 2, 5, 10, 16, 25, 35, 48,
	63, 80, 100, 122, 147, 174, 204, 237,
	272, 310, 351, 395, 442, 492, 545, 601,
	660, 723, 788, 857, 929, 1004, 1083, 1165,
	1250, 1339, 1432, 1527, 1627, 1730, 1836, 1946,
	2060, 2177, 2298, 2423, 2552, 2684, 2820, 2960,
	3104, 3252, 3403, 3558, 3718, 3881, 4048, 4220,
	4395, 4574, 4758, 4945, 5137, 5333, 5533, 5737,
	5945, 6158, 6374, 6595, 6820, 7050, 7284, 7522,
	7764, 8011, 8262, 8518, 8778, 9042, 9311, 9584,
	9862, 10144, 10431, 10723, 11018, 11319, 11624, 11933,
	12248, 12566, 12890, 13218, 13551, 13888, 14230, 14577,
	14929, 15285, 15646, 16012, 16383
};

#elif FADE_STATUS_PWM_BITS == 15
/* 101-step brightness table: gamma = 2.3 for 15-bit PWM*/ 
const flvar_t FadeStatusGammaTable[101] PROGMEM = {
	0, 1, 4, 10, 20, 33, 51, 72,
	98, 129, 164, 204, 250, 300, 356, 417,
	484, 557, 635, 719, 809, 905, 1007, 1115,
	1230, 1351, 1479, 1613, 1753, 1901, 2055, 2216,
	2384, 2559, 2741, 2929, 3126, 3329, 3539, 3757,
	3983, 4215, 4456, 4703, 4959, 5222, 5493, 5771,
	6057, 6352, 6654, 6964, 7282, 7608, 7942, 8285,
	8635, 8994, 9361, 9736, 10120, 10512, 10913, 11322,
	11740, 12166, 12600, 13044, 13496, 13957, 14427, 14905,
	15392, 15888, 16393, 16907, 17430, 17962, 18504, 19054,
	19613, 20181, 20759, 21346, 21942, 22548, 23162, 23787,
	24420, 25063, 25715, 26377, 27049, 27730, 28420, 29121,
	29830, 30550, 31279, 32018, 32767
};

#elif FADE_STATUS_PWM_BITS == 16
/* 101-step brightness table: gamma = 2.3 for 16-bit PWM*/ 
const flvar_t FadeStatusGammaTable[101] PROGMEM = {
	0, 2, 8, 21, 40, 67, 101, 145,
	197, 258, 328, 409, 500, 601, 712, 835,
	968, 1113, 1269, 1437, 1617, 1810, 2014, 2231,
	2460, 2702, 2957, 3226, 3507, 3802, 4110, 4432,
	4768, 5117, 5481, 5859, 6251, 6658, 7079, 7515,
	7965, 8431, 8911, 9407, 9918, 10444, 10985, 11542,
	12115, 12704, 13308, 13928, 14564, 15216, 15885, 16569,
	17271, 17988, 18722, 19473, 20240, 21025, 21826, 22644,
	23479, 24332, 25201, 26088, 26993, 27914, 28854, 29810,
	30785, 31777, 32787, 33815, 34861, 35925, 37008, 38108,
	39227, 40364, 41519, 42693, 43885, 45096, 46325, 47574,
	48841, 50127, 51432, 52756, 54099, 55461, 56842, 58242,
	59662, 61101, 62560, 64037, 65535
};

#else
  #error PWM resolution not supported for Gamma correction
#endif

#endif