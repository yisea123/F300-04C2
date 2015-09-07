/*************************************************
Project:                GM8804C-2_ARM
File name:              AD.c
Description:            AD驱动相关函数
Author:                 丛海旭
Version:                1.0
Date:                   2013-12-9
Others:                 IC:CS5532
History:
*************************************************/

#include "include.h"

#define ADSPEED_120  0
#define ADSPEED_240  1
#define ADSPEED_480  2
#define ADSPEED_960  3


#ifdef ADFILTER_02CS
//GM8802C-S仪表的滤波数组
//ADC采用120次/S的速度时使用的滤波参数
const u32 DF0TAB120[]={488,743,1010,1284,1560,1834,2099,2351,2584,2793,2975,3126,3241,3320,3360};
const u32 DF1TAB120[]={289,434,585,741,900,1062,1224,1384,1541,1692,1836,1972,2097,2209,2309,2394,2463,2516,2551,2569};
const u32 DF2TAB120[]={45,141,243,350,462,578,697,818,940,1061,1182,1300,1415,1526,1632,1732,1824,1908,1984,2050,2107,2152,2187,2210,2224};
const u32 DF3TAB120[]={50,115,184,256,331,409,488,569,651,734,817,899,981,1062,1141,1217,1292,1362,1430,1493,1552,1606,1655,1699,1737,1769,1794,1814,1827,1834};
const u32 DF4TAB120[]={19,69,120,172,227,283,341,400,460,521,583,646,708,770,832,892,952,1011,1068,1123,1177,1228,1276,1322,1364,1404,1440,1472,1501,1526,1547,1564,1576,1585,1589};
const u32 DF5TAB120[]={16,54,92,132,173,215,258,302,348,394,440,488,535,583,630,678,725,771,817,862,907,950,992,1032,1071,1108,1143,1177,1208,1237,1264,1289,1311,1330,1347,1361,1372,1381,1386,1389};
const u32 DF6TAB120[]={12,44,74,104,136,169,203,237,272,308,344,381,418,455,493,530,568,605,642,679,715,751,786,821,855,887,919,950,979,1007,1034,1060,1084,1106,1127,1146,1163,1178,1192,1204,1214,1222,1228,1232,1234};
const u32 DF7TAB120[]={9,32,58,83,108,135,162,189,217,246,275,304,334,364,394,424,455,485,515,546,576,606,635,665,694,722,750,777,803,829,854,878,901,923,944,964,983,1001,1017,1033,1047,1060,1071,1081,1090,1097,1103,1107,1110,1112};
const u32 DF8TAB120[]={19,38,58,78,99,120,142,164,186,209,233,256,280,304,329,353,378,402,427,452,476,501,525,549,573,597,620,643,666,688,710,731,752,772,791,810,828,845,862,877,892,906,919,932,943,953,963,971,978,985,990,994,997,1000,1002};
const u32 DF9TAB120[]={11,27,44,61,78,96,114,132,151,170,190,210,230,250,270,291,312,333,353,374,395,416,437,458,479,500,520,540,560,580,599,619,637,656,674,691,708,725,741,757,772,786,800,813,825,837,848,859,868,877,885,893,899,905,910,914,918,921,923,926};
const u32 DFNUMBER120[]={30,40,50,60,70,80,90,100,110,120};
static u32 const DEF_FILTER120[]={65536,65536,65536,65536,65536,65536,65536,65536,65536,65536};
const u32* pu32DFTab_120[10]={DF0TAB120,DF1TAB120,DF2TAB120,DF3TAB120,DF4TAB120,DF5TAB120,DF6TAB120,DF7TAB120,DF8TAB120,DF9TAB120};

//ADC采用240次/S的速度时使用的滤波参数  
u32 const DF0TAB240[]={0,15207,42219,79705,125558,177052,231039,284190,333236,375212,407679,428902};
u32 const DF1TAB240[]={0,2895,7219,12936,19980,28267,37686,48107,59385,71357,83846,96671,109640,122560,135241,147494,159140,170009,179947,188814,196492,202882,207909,211522};
u32 const DF2TAB240[]={0,1162,2741,4732,7127,9916,13083,16611,20480,24668,29148,33894,38875,44060,49417,54910,60503,66162,71848,77525,83155,88703,94132,99407,104495,109362,113979,118316,122348,126049,129399,132379,134972,137167,138953,140324};
u32 const DF3TAB240[]={9,18,47,98,179,296,461,685,984,1375,1877,2510,3296,4260,5424,6814,8455,10371,12583,15112,17978,21192,24768,28708,33015,37682,42697,48040,53687,59603,65749,72077,78536,85067,91606,98085,104436,110586,116462,121994,127112,131751,135850,139355,142219,144402,145874,146615};
u32 const DF4TAB240[]={7,12,26,51,89,142,214,308,431,586,781,1023,1318,1676,2105,2614,3213,3911,4718,5646,6703,7899,9243,10745,12411,14250,16267,18465,20849,23420,26176,29116,32235,35527,38981,42588,46333,50200,54172,58229,62348,66506,70677,74834,78949,82995,86941,90758,94417,97889,101147,104163,106914,109375,111525,113347,114824,115944,116695,117073};
u32 const DF5TAB240[]={6,9,17,31,52,80,118,166,227,303,397,511,648,811,1006,1234,1500,1810,2166,2573,3037,3562,4153,4815,5552,6369,7270,8261,9344,10523,11802,13184,14670,16263,17962,19769,21684,23704,25828,28053,30375,32789,35290,37872,40526,43245,46018,48838,51691,54568,57456,60342,63213,66055,68856,71600,74274,76863,79354,81734,83988,86104,88070,89874,91507,92957,94217,95279,96137,96785,97219,97437};
u32 const DF6TAB240[]={5,7,12,21,33,50,73,101,136,178,230,291,365,451,553,671,808,966,1147,1352,1586,1849,2144,2474,2842,3249,3699,4195,4738,5331,5977,6678,7436,8253,9131,10072,11077,12148,13285,14490,15761,17101,18507,19980,21518,23121,24785,26510,28292,30127,32014,33947,35922,37935,39980,42052,44145,46253,48369,50487,52599,54699,56780,58832,60850,62826,64752,66620,68423,70154,71805,73371,74844,76217,77486,78645,79688,80611,81410,82082,82623,83030,83303,83440};
u32 const DF7TAB240[]={4,5,9,15,23,34,48,66,88,114,145,183,226,277,336,404,483,572,674,789,919,1065,1228,1410,1612,1836,2083,2354,2652,2977,3331,3715,4132,4582,5067,5589,6148,6746,7384,8063,8784,9548,10356,11208,12105,13046,14033,15065,16142,17263,18428,19637,20887,22178,23509,24878,26282,27721,29191,30690,32215,33764,35334,36921,38521,40132,41748,43368,44985,46597,48199,49787,51356,52902,54420,55907,57357,58767,60132,61447,62709,63914,65057,66136,67146,68084,68948,69733,70439,71061,71599,72050,72412,72685,72868,72959};
u32 const DF8TAB240[]={4,5,7,11,17,24,34,46,61,78,98,122,150,183,220,262,311,366,428,498,577,664,762,871,991,1124,1270,1430,1605,1796,2005,2231,2476,2741,3026,3334,3664,4017,4395,4797,5226,5682,6166,6677,7218,7788,8389,9019,9681,10374,11099,11855,12643,13462,14313,15195,16108,17051,18024,19026,20056,21114,22198,23307,24440,25595,26772,27967,29180,30409,31651,32905,34168,35438,36714,37991,39269,40544,41814,43076,44327,45565,46787,47991,49172,50330,51460,52561,53629,54662,55658,56613,57527,58395,59216,59988,60709,61376,61989,62546,63044,63483,63862,64179,64433,64625,64753,64817};
u32 const DF9TAB240[]={3,4,6,9,13,18,25,34,44,56,70,87,105,127,152,180,212,248,289,334,385,441,503,572,648,732,824,925,1034,1154,1284,1425,1578,1743,1921,2112,2317,2537,2772,3023,3290,3575,3877,4198,4537,4896,5274,5673,6092,6533,6995,7479,7985,8514,9066,9640,10237,10857,11500,12167,12856,13568,14302,15059,15837,16637,17458,18299,19159,20039,20937,21852,22784,23731,24693,25668,26655,27653,28661,29676,30699,31726,32758,33791,34826,35859,36889,37915,38935,39946,40948,41938,42915,43877,44821,45747,46652,47535,48394,49227,50032,50809,51554,52268,52947,53592,54200,54771,55302,55793,56243,56651,57016,57337,57613,57845,58030,58170,58263,58310};
u32 const DFNUMBER240[]={24,48,72,96,120,144,168,192,216,240};
static u32 const DEF_FILTER240[]={4999998,4999998,5000004,5000000,5000002,5000006,5000000,4999996,5000004,4999998};
const u32* pu32DFTab_240[10]={DF0TAB240,DF1TAB240,DF2TAB240,DF3TAB240,DF4TAB240,DF5TAB240,DF6TAB240,DF7TAB240,DF8TAB240,DF9TAB240};
//ADC采用480次/S的速度时使用的滤波参数
static u32 const DF0TAB480[] = {0,2895,7219,12936,19981,28267,37686,48108,59385,71357,83847,96671,109640,122560,135241,147494,159140,170009,179947,188814,196492,202882,207909,211522};
static u32 const DF1TAB480[] = {0,619,1413,2380,3519,4827,6300,7934,9725,11667,13753,15978,18333,20811,23403,26101,28893,31772,34726,37746,40819,43935,47083,50251,53427,56601,59760,62894,65990,69037,72025,74943,77780,80527,83172,85709,88126,90417,92574,94589,96456,98169,99723,101114,102338,103391,104272,104978};
static u32 const DF2TAB480[] = {0,260,572,935,1348,1812,2326,2890,3503,4163,4871,5626,6426,7270,8157,9087,10056,11065,12112,13195,14312,15461,16642,17852,19089,20352,21638,22945,24271,25615,26973,28344,29726,31117,32513,33914,35316,36718,38116,39510,40897,42273,43639,44990,46325,47642,48939,50213,51463,52687,53883,55048,56182,57282,58347,59375,60364,61314,62223,63089,63911,64688,65419,66104,66741,67329,67868,68357,68796,69184,69521,69807};
static u32 const DF3TAB480[] = {4,5,9,15,23,34,48,66,88,114,145,183,226,277,336,404,483,572,674,789,919,1065,1228,1410,1612,1836,2083,2354,2652,2977,3331,3715,4132,4582,5068,5589,6148,6746,7384,8063,8784,9549,10356,11208,12105,13047,14033,15065,16142,17263,18429,19637,20887,22179,23509,24878,26282,27721,29191,30690,32215,33765,35334,36921,38521,40132,41748,43368,44985,46597,48199,49787,51356,52902,54420,55907,57357,58767,60131,61447,62709,63913,65057,66135,67146,68084,68947,69733,70438,71061,71598,72049,72412,72685,72867,72959};
static u32 const DF4TAB480[] = {3,4,6,9,13,18,25,34,44,56,70,87,105,127,152,180,212,248,289,334,385,441,503,572,648,732,824,925,1035,1154,1284,1425,1578,1743,1921,2112,2317,2537,2772,3023,3291,3575,3878,4198,4537,4896,5274,5673,6093,6533,6995,7479,7986,8514,9066,9640,10237,10857,11501,12167,12856,13568,14302,15059,15837,16637,17458,18299,19160,20039,20937,21853,22784,23732,24693,25668,26655,27653,28661,29676,30699,31726,32758,33791,34826,35859,36889,37915,38935,39946,40948,41938,42915,43876,44821,45747,46652,47535,48393,49226,50032,50808,51554,52267,52947,53592,54200,54770,55301,55793,56243,56651,57015,57336,57613,57844,58030,58169,58263,58309};
static u32 const DF5TAB480[] = {3,3,4,6,8,11,15,20,26,32,40,48,58,70,82,96,112,130,150,172,196,223,252,284,320,358,400,446,496,550,608,672,740,813,892,976,1067,1164,1268,1378,1496,1622,1755,1896,2045,2204,2371,2548,2734,2930,3136,3353,3580,3818,4068,4328,4601,4885,5182,5490,5812,6146,6492,6852,7224,7610,8009,8421,8847,9285,9738,10203,10682,11173,11678,12196,12726,13269,13824,14391,14970,15561,16163,16776,17399,18032,18675,19327,19987,20656,21333,22016,22706,23402,24102,24808,25517,26229,26944,27660,28377,29094,29811,30525,31238,31947,32652,33353,34047,34735,35416,36088,36751,37403,38045,38675,39292,39896,40486,41060,41618,42160,42684,43190,43676,44144,44590,45016,45420,45802,46161,46497,46809,47096,47359,47597,47809,47996,48156,48290,48397,48478,48532,48559};
static u32 const DF6TAB480[] = {2,3,3,4,6,8,10,13,16,20,25,30,36,43,50,58,67,77,88,100,114,128,144,162,180,201,223,247,273,302,332,364,400,437,477,520,566,616,668,724,783,846,913,984,1059,1138,1221,1310,1403,1501,1604,1712,1826,1945,2070,2201,2338,2481,2631,2787,2950,3119,3295,3479,3669,3867,4073,4286,4506,4734,4971,5215,5467,5727,5995,6272,6557,6850,7152,7461,7780,8106,8441,8785,9136,9496,9864,10240,10625,11017,11417,11825,12240,12663,13093,13530,13975,14426,14883,15347,15817,16293,16775,17261,17753,18250,18751,19256,19765,20277,20793,21311,21832,22354,22878,23404,23930,24456,24982,25508,26033,26556,27078,27597,28114,28627,29137,29643,30144,30640,31130,31614,32092,32563,33027,33482,33930,34368,34798,35217,35627,36026,36414,36791,37156,37509,37850,38178,38492,38794,39081,39354,39612,39856,40085,40299,40497,40679,40845,40996,41130,41247,41348,41433,41500,41551,41585,41602};
static u32 const DF7TAB480[] = {2,2,3,3,4,6,7,9,11,14,17,20,24,28,33,38,44,50,57,64,72,81,90,101,112,124,137,151,166,183,200,219,239,260,283,308,333,361,390,422,455,490,527,566,608,651,698,746,797,851,908,968,1030,1095,1164,1236,1311,1390,1472,1557,1647,1740,1837,1938,2043,2152,2265,2383,2505,2631,2763,2898,3039,3184,3335,3490,3650,3815,3986,4161,4342,4528,4720,4917,5119,5327,5541,5760,5984,6214,6450,6691,6938,7190,7449,7712,7981,8256,8536,8822,9113,9409,9711,10018,10330,10648,10970,11297,11629,11966,12307,12653,13003,13358,13716,14079,14445,14815,15189,15566,15946,16329,16714,17103,17493,17886,18281,18678,19076,19476,19877,20278,20681,21083,21486,21889,22291,22692,23093,23493,23891,24288,24682,25075,25465,25852,26236,26617,26994,27367,27737,28102,28462,28817,29167,29512,29851,30183,30510,30830,31143,31450,31749,32040,32324,32600,32868,33127,33378,33620,33853,34076,34291,34495,34690,34875,35050,35215,35369,35513,35647,35769,35881,35982,36072,36151,36219,36275,36321,36355,36377,36389};
static u32 const DF8TAB480[] = {2,2,2,3,4,4,6,7,8,10,12,14,17,20,23,26,30,34,39,44,49,55,61,67,75,82,91,99,109,119,130,142,154,167,181,196,212,229,247,266,286,307,329,353,378,404,431,460,491,523,556,592,629,667,708,750,795,841,889,940,993,1047,1104,1164,1226,1290,1357,1426,1498,1573,1650,1730,1813,1899,1988,2080,2175,2273,2374,2479,2587,2698,2812,2930,3052,3176,3305,3437,3572,3712,3855,4001,4152,4306,4464,4626,4792,4961,5135,5312,5494,5679,5868,6061,6258,6459,6664,6873,7086,7302,7523,7747,7975,8207,8443,8682,8925,9171,9422,9675,9933,10193,10457,10724,10995,11268,11545,11825,12107,12392,12680,12971,13264,13560,13858,14158,14460,14764,15070,15378,15688,15999,16311,16624,16939,17254,17571,17887,18205,18523,18841,19159,19477,19794,20111,20428,20744,21059,21373,21686,21997,22306,22614,22920,23224,23526,23825,24121,24415,24706,24994,25278,25559,25836,26110,26379,26645,26906,27163,27415,27662,27905,28142,28374,28601,28822,29038,29248,29452,29650,29842,30027,30206,30379,30544,30704,30856,31001,31139,31270,31394,31510,31619,31721,31815,31901,31980,32051,32114,32170,32217,32257,32289,32313,32328,32336};
static u32 const DF9TAB480[] = {2,2,2,2,3,4,4,5,6,8,9,11,13,15,17,19,22,25,28,31,35,39,43,47,52,58,63,69,75,82,89,97,105,114,123,133,143,154,166,178,191,204,219,234,250,266,284,302,321,342,363,385,409,433,458,485,513,542,572,604,637,671,706,744,782,822,864,907,952,998,1046,1096,1148,1202,1257,1314,1373,1435,1498,1563,1630,1700,1771,1845,1921,1999,2080,2163,2248,2336,2426,2518,2613,2711,2811,2913,3018,3126,3237,3350,3466,3584,3706,3830,3956,4086,4218,4354,4492,4633,4776,4923,5072,5225,5380,5538,5699,5862,6029,6199,6371,6546,6724,6905,7088,7274,7463,7655,7849,8047,8246,8449,8654,8861,9071,9283,9498,9715,9935,10157,10381,10607,10835,11066,11298,11532,11768,12006,12246,12488,12731,12975,13221,13469,13717,13967,14218,14470,14723,14977,15232,15487,15743,16000,16256,16514,16771,17028,17286,17543,17801,18057,18314,18570,18825,19080,19333,19586,19838,20088,20338,20586,20832,21077,21320,21561,21800,22037,22272,22505,22735,22963,23188,23410,23630,23846,24060,24270,24477,24681,24881,25078,25271,25460,25645,25827,26004,26177,26346,26511,26671,26827,26978,27124,27266,27403,27535,27662,27784,27901,28013,28120,28221,28317,28408,28493,28573,28647,28716,28779,28836,28888,28934,28975,29009,29038,29061,29079,29090,29096};
static u32 const DEF_FILTER480[] = {5000004,5000000,4999996,4999992,4999992,4999998,4999994,4999992,4999992,4999998};
static u32 const DFNUMBER480[] = {48,96,144,192,240,288,336,384,432,480};
const u32* pu32DFTab_480[10]={DF0TAB480,DF1TAB480,DF2TAB480,DF3TAB480,DF4TAB480,DF5TAB480,DF6TAB480,DF7TAB480,DF8TAB480,DF9TAB480};

#else

u32 const DFNUMBER[]={19,27,35,43,51,59,67,75,83,91};
//各级滤波系数表
u32 const DFTAB0[]={76,163,256,351,443,527,597,651,684,696};
                    /*6*/
u32 const DFTAB1[]={13,57,105,156,209,263,315,364,409,447,479,502,516,522};
                    /*4.5*/
u32 const DFTAB2[]={4,29,56,86,117,149,182,214,245,275,303,328,351,370,385,396,403,406};
                    /*3.50*/
u32 const DFTAB3[]={6,22,41,59,79,99,119,140,161,181,201,220,238,255,270,284,296,306,314,320,323,324};
                    /*2.8*/
u32 const DFTAB4[]={1,12,25,38,52,66,81,95,110,126,141,155,170,184,197,210,222,233,243,252,259,265,270,274,276,278,};
                    /*2.39*/
u32 const DFTAB5[]={1,9,19,28,38,48,59,70,81,92,103,115,126,137,147,158,
                    168,177,186,195,203,210,217,222,227,231,234,237,238,240};
                    /*2.06*/
u32 const DFTAB6[]={1,8,15,23,30,38,46,54,63,71,80,88,97,105,114,122,130,138,
                    146,153,160,167,173,179,184,189,194,198,201,204,206,207,208,208,};
                    /*1.8*/
u32 const DFTAB7[]={1,7,12,18,24,30,36,42,49,56,62,69,76,83,90,97,103,110,116,
                    123,129,135,141,146,151,156,161,165,169,173,176,179,181,182,184,185,186,186};
                    /*1.61*/
u32 const  DFTAB8[]={2,6,10,15,20,24,29,35,40,45,51,56,62,67,73,78,84,89,
                     95,100,105,110,115,120,125,130,134,138,142,146,149,152,
                     155,158,160,162,164,165,166,167,168,168};
                   /*1.45*/
u32 const  DFTAB9[]={3,6,10,14,17,21,26,30,34,38,43,47,52,56,61,65,70,74,
                     79,83,88,92,96,100,104,108,112,116,120,123,126,129,
                     132,135,138,140,142,144,146,147,149,150,151,151,152,152};
                   //1.31

#define DFCOESUM  8192
static u32 const DEF_FILTER[]={8192,8192,8192,8192,8192,8192,8192,8192,8192,8192};
const u32* pu32DFTab[10]={DFTAB0,DFTAB1,DFTAB2,DFTAB3,DFTAB4,DFTAB5,DFTAB6,DFTAB7,DFTAB8,DFTAB9};

#endif





//读cs5532输出
#define ADC_DOUT_READ   GPIO_BitRead(GPIO0,0)
//#define ADC_DOUT_CLR    GPIO_BitWrite(GPIO0,0,0)
//#define ADC_DOUT_SET    GPIO_BitWrite(GPIO0,0,1)
//写cs5532输入端口
#define ADC_DIN_CLR     GPIO_BitWrite(GPIO0,1,0)
#define ADC_DIN_SET     GPIO_BitWrite(GPIO0,1,1)
//写cs5532时钟端口
#define ADC_CLK_CLR     GPIO_BitWrite(GPIO0,2,0)
#define ADC_CLK_SET     GPIO_BitWrite(GPIO0,2,1)


//同步字符 以及同步字符 字长度
#define  ADCOM_SYNC1        0XFF
#define  ADCOM_SYNC0        0XFE
#define  ADCOM_SYNC1_NUM    15
#define  ADCOM_SYNC0_NUM    1

#define ADCOM_WOFFSETR      0X01    //写偏移寄存器
#define ADCOM_WGAINR        0X02    //写增益寄存器
#define ADCOM_WCFGR         0X03    //写配置寄存器
#define ADCOM_RCFGR         0X0B    //读配置寄存器
#define ADCOM_WCANNELR      0X05    //写通道设置寄存器

#define ADDAT_CFG_RESET 0x22000000  //复位
#define ADDAT_CFG_NRM   0x02000000  //正常
#define ADDAT_OSR_0     0x00000000  //Offset==0
#define ADDAT_GR_1      0x01000000  //Gain  == 1
#define ADDAT_CR_3840   0x04400440  //3840次/秒
#define ADDAT_CR_1920   0x04C004C0  //1920次/秒
#define ADDAT_CR_960    0x05400540  //960次/秒
#define ADDAT_CR_480    0x05C005C0  //480次/秒
#define ADDAT_CR_240    0x06400640  //240次/秒
#define ADDAT_CR_120    0x00400040  //120次/秒
#define ADDAT_CR_60     0x00C000C0  //60次/秒

#define ADCOM_ADStar        0XC0
#define ADCOM_KEEP          0X00

bool gb_AdErrFlg;           //AD错误标志
bool gb_AdOKFlg;            //AD初始化成功标志位
bool gb_AdOflFlg;           //AD溢出标志位
bool gb_OflFlg;             //重量溢出标志位
bool gb_SigWtFlg;             //符号标志

#ifdef ADFILTER_02CS
#define ADQUEUE_LENGTH  480
u32 gu32_AdQueue[ADQUEUE_LENGTH];       //AD采样队列
#else
#define ADQUEUE_LENGTH  92
u32 gu32_AdQueue[ADQUEUE_LENGTH];       //AD采样队列
#endif


u32 gu32_AdValue;           //AD转换得到的数据

/*********************************************************************
函数名称: void AD_SendByte(u8 outdata)
功    能: 写入ADC一字节数据
说    明: 底层驱动
入口参数: outdata = 发送的数据
返 回 值: 
设    计: 丛海旭               时    间: 2013-12-10
修    改:                      时    间: 
*********************************************************************/
void AD_SendByte(u8 outdata)
{
    u8 i;
    for (i = 0; i < 8; i++)
    {
        (outdata & 0x80) ? ADC_DIN_SET:ADC_DIN_CLR;
        __nop();
        ADC_CLK_SET;
        __nop();
        outdata <<= 1;
        ADC_CLK_CLR;
        __nop();
    }
}

/*********************************************************************
函数名称: u8 AD_ReceiveByte(void)
功    能: 从ADC读出一字节数据
说    明: 底层驱动
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2013-12-10
修    改:                      时    间: 
*********************************************************************/
u8 AD_ReceiveByte(void)
{
    u8 i;
    u8 indata = 0;
    for (i = 0; i < 8; i++)
    {
        indata <<= 1;
        if(ADC_DOUT_READ == 1)
            indata |= 0X01;
        ADC_CLK_SET;
        __nop();
        ADC_CLK_CLR;
        __nop();

    }
    return indata;
}

/*********************************************************************
函数名称: void AD_WriteReg(u8 u8AdCOM,u32 u32AdRegVal)
功    能: 写ADC寄存器
说    明: 底层驱动
入口参数: 
返 回 值: u8AdCOM：寄存器地址 u32AdRegVal：寄存器值
设    计: 丛海旭               时    间: 2013-12-10
修    改:                      时    间: 
*********************************************************************/
void AD_WriteReg(u8 u8AdCOM,u32 u32AdRegVal)
{
    u8 i;
    ULDATA uADData;
    uADData.ul=u32AdRegVal;
    AD_SendByte(u8AdCOM);
    for(i=0;i<4;i++){
        AD_SendByte(uADData.uc[3-i]); //ARM 小端模式//先发送高位
    }
}

/*********************************************************************
函数名称: u32 AD_ReadReg(u8 u8AdCOM)
功    能: 读ADC寄存器
说    明: 底层驱动
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2013-12-10
修    改:                      时    间: 
*********************************************************************/
u32 AD_ReadReg(u8 u8AdCOM)
{
    ULDATA u32AdRegVal;
    u8 i;
    AD_SendByte(u8AdCOM);
    for (i = 0; i < 4; i++)
        u32AdRegVal.uc[3-i] = AD_ReceiveByte();//ARM 小端模式//先接收的是高位
    return u32AdRegVal.ul;
}

/*********************************************************************
函数名称: void AD_SYNC(void)
功    能: 发送同步命令
说    明: 底层驱动
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2013-12-10
修    改:                      时    间: 
*********************************************************************/
void AD_SYNC(void)
{
    u8 i;
    for (i = 0; i < ADCOM_SYNC1_NUM; i++)
        AD_SendByte(ADCOM_SYNC1);
    for (i = 0; i < ADCOM_SYNC0_NUM; i++)
        AD_SendByte(ADCOM_SYNC0);
}

/*********************************************************************
函数名称: bool AD_Init(u8 i)
功    能: 初始化AD
说    明: 底层驱动
入口参数: i:对应AD采样速度120 240 480 960 
返 回 值: 
设    计: 丛海旭               时    间: 2013-12-10
修    改:                      时    间: 
*********************************************************************/
bool AD_Init(u8 i)
{
    u8 u8reInitNum=0;
    u32 u32CfgRegVal;
    u32 lu32_Temp;
    
    switch (i)
    {
        default:
        case 0:
            lu32_Temp = ADDAT_CR_120;
            break;
        case 1:
            lu32_Temp = ADDAT_CR_240;
            break;
        case 2:
            lu32_Temp = ADDAT_CR_480;
            break;
        case 3:
            lu32_Temp = ADDAT_CR_960;
            break;
    }
    
    //标准TTL输入，GPIO_IN_TRI_CMOS高阻模拟输入
    GPIO_Config(GPIO0, (1<<0), GPIO_IN_TRI_TTL);
    //推挽输出GPIO_OUT_PP
    GPIO_Config(GPIO0, (1<<1), GPIO_OUT_PP);
    //时钟 推挽输出
    GPIO_Config(GPIO0, (1<<2), GPIO_OUT_PP);
    
    do{
        //判断重新初始化次数是否已经超出，超出则AD初始化失败
        if (u8reInitNum >= 4)
        {
            gb_AdErrFlg = true;
            return false;
        }
        AD_SYNC();      //发同步字符初始化到命令模式
        AD_WriteReg(ADCOM_WCFGR, ADDAT_CFG_RESET); //写复位命令
        u8reInitNum++;  //自加 AD重初始化次数
        u32CfgRegVal = AD_ReadReg(ADCOM_RCFGR); //读配置寄存器
    }while(u32CfgRegVal != 0x10000000);     //已经复位成功则继续

    AD_WriteReg(ADCOM_WOFFSETR, ADDAT_OSR_0);      //写偏移寄存器 偏移量为0
    AD_WriteReg(ADCOM_WGAINR, ADDAT_GR_1);         //写增益寄存器 增益为1
    AD_WriteReg(ADCOM_WCFGR, ADDAT_CFG_NRM);       //写配置寄存器 参考电压设置为1V~2.5V
    //写通道设置寄存器 物理通道1 增益1 转换次数120 单极性
    AD_WriteReg(ADCOM_WCANNELR, lu32_Temp);
    AD_SendByte(ADCOM_ADStar);    //AD执行连续转换
    delay(1);
    gb_AdErrFlg = false;
    return true;            //初始化成功
}


u32 DEFSUMTab(u8 dflevel)
{
    if (dflevel > 9)
        dflevel = 5;
#ifdef ADFILTER_02CS
    switch (gs_Setup.AdSamplingRate)
    {
        case ADSPEED_120:
            return (DEF_FILTER120[dflevel]);
        case ADSPEED_240:
            return (DEF_FILTER240[dflevel]);
        case ADSPEED_480:
        case ADSPEED_960:
        default:
            return (DEF_FILTER480[dflevel]);
    }
#else
    return (DEF_FILTER[dflevel]);
#endif
}



/*程序的入口是滤波的级数，而出口是指向该级数的表格的指针*/
const u32* FilterTab(u8 dflevel)
{
    if (dflevel > 9)
        dflevel = 5;
#ifdef ADFILTER_02CS
    switch (gs_Setup.AdSamplingRate)
    {
        case ADSPEED_120:
            return (pu32DFTab_120[dflevel]);
        case ADSPEED_240:
            return (pu32DFTab_240[dflevel]);
        case ADSPEED_480:
        case ADSPEED_960:
        default:
            return (pu32DFTab_480[dflevel]);
    }
#else
    return (pu32DFTab[dflevel]);
#endif
}

/*程序的入口是滤波的级数，而出口是指向该级数的表格的指针*/
u32 DFNumberTab(u8 dflevel)
{
    if (dflevel > 9)
        dflevel = 5;
#ifdef ADFILTER_02CS
    switch (gs_Setup.AdSamplingRate)
    {
        case ADSPEED_120:
            return (DFNUMBER120[dflevel]);
        case ADSPEED_240:
            return (DFNUMBER240[dflevel]);
        case ADSPEED_480:
        case ADSPEED_960:
        default:
            return (DFNUMBER480[dflevel]);
    }
#else
    return (DFNUMBER[dflevel]);
#endif
}

/*********************************************************************
函数名称: void Refresh_RefreshAdArray(bool* fb_RefreshFlg, u32* fu32p_AdArray, u32 fu32_Num)
功    能: 刷新采样数组队列
说    明: 
入口参数: fb_RefreshFlg=刷新标志位地址
          fu32p_AdArray=AD采样队列地址
          fu32_Num=滤波算法数据个数
返 回 值: 
设    计: 丛海旭               时    间: 2015-07-08
修    改:                      时    间: 
*********************************************************************/
#ifdef REFRESH_AT_SP23_MAX
void Refresh_RefreshAdArray(bool* fb_RefreshFlg, u32* fu32p_AdArray, u32 fu32_Num)
{
//    u32 lu32_Temp;
    u32 lu32_Temp1;
    u16 i;
    
    if (*fb_RefreshFlg)
    {   //刷新采样数组
//        lu32_Temp = fu32_Num / 3;   //用2个数据平均值刷新后面的数组
//        lu32_Temp = 2;   //用2个数据平均值刷新后面的数组
//        if (lu32_Temp > 0)
//        {
//            for (i = 0; i < lu32_Temp; i++)
//            {   //计算总和
//                lu32_Temp1 += fu32p_AdArray[0] + fu32p_AdArray[1][i];
//            }
            lu32_Temp1 = (fu32p_AdArray[0] + fu32p_AdArray[1]) / 2;
//            lu32_Temp1 /= lu32_Temp;    //算平均值
            for (i = 2; i < fu32_Num; i++)
            {   //刷新后续数组
                fu32p_AdArray[i] = lu32_Temp1;
            }
            *fb_RefreshFlg = false;
//        }
//        else
//        {
//            *fb_RefreshFlg = false;
//        }
    }
}
#endif

/*********************************************************************
函数名称: u32 Ad_Filter(u32 ful_AdResult, u32 fu32_FLevel)
功    能: AD滤波处理
说    明: 参考单片机版本c2程序
入口参数: ful_AdResult：AD转换结果。fu32_FLevel：滤波级数
返 回 值: 
设    计: 丛海旭               时    间: 2013-12-10
修    改:                      时    间: 
*********************************************************************/
u32 Ad_Filter(u32 ful_AdResult, u32 fu32_FLevel)
{
    u32  sumnumber;
    u32  i,j;
    const u32 *adtpoint;
    u64 adresult;
    u32 *adpoint1;
    u32 *adpoint2;
    
    //-------------------------------------------------
    /*加料、定值和卸料过程中的滤波参数可以自由设置，滤波参数由小切换到大后，由于参与滤波计算的数组
    变长，可能出现重量跳变问题。如卸料时滤波较小，卸料完成后变为大滤波，由于滤波数组变长，后面增加
    的长度里面的数据要比前面的大（因为卸料过程重量是减小状态），可能导致滤波切换时重量变大问题。
    为防止以上问题，在滤波参数变化前，进行采样数组刷新，用当前数组中的平均值来刷新后面的数组值。*/
    //测试效果滤波级数切换时会有重量跳变，改用当前滤波后的数据来刷新数组 2015-7-28 丛海旭
    static u32 su32_FLevel = 9;
    if (fu32_FLevel > su32_FLevel)
    {   //滤波参数由小变大刷新增加后的数组中重量
//         for (i = 0, adresult = 0; i < DFNumberTab(su32_FLevel); i++)
//            adresult += gu32_AdQueue[i];
//        adresult /= i;
//        //刷新后面的数组值为计算的平均值
        //刷新后面的数组为上次滤波值
        
        for (j = DFNumberTab(su32_FLevel); j < DFNumberTab(fu32_FLevel); j++)
            gu32_AdQueue[j] = gu32_AdFedValue;
    }
    su32_FLevel = fu32_FLevel;
    //---------------------------------------------------
#ifdef REFRESH_AT_SP23_MAX
    Refresh_RefreshAdArray(&gb_RefreshAdArrayFlg, gu32_AdQueue, DFNumberTab[fu32_FLevel]);
#endif
    //将采样数组后移，新数据存入数组gu32_AdQueue[0]中
    adpoint1 = gu32_AdQueue + ADQUEUE_LENGTH - 1;
    adpoint2 = gu32_AdQueue + ADQUEUE_LENGTH - 2;
    for(; adpoint1 > gu32_AdQueue ;adpoint1--, adpoint2--)
        *adpoint1 = *adpoint2;
    adpoint1 = gu32_AdQueue;
    *adpoint1 = ful_AdResult;

    adresult = 0;
    adtpoint = FilterTab(fu32_FLevel);         /*指针指向对应的表格*/
#ifdef ADFILTER_02CS    //02CS滤波计算数组个数是偶数
    sumnumber = DFNumberTab(fu32_FLevel) / 2;        /*取得系数的个数*/
    //因为滤波数组前后的数据是相同的，所以下面这样计算可以节省一半的循环时间
    for (i = 0; i < sumnumber; i++, adtpoint++)
        adresult += ((u64)(*adtpoint) * (gu32_AdQueue[i] + gu32_AdQueue[DFNumberTab(fu32_FLevel)-1-i]));
    adresult /= DEFSUMTab(fu32_FLevel);
#else   //04C2滤波计算数组个数是奇数
    sumnumber = (DFNumberTab(fu32_FLevel) - 1) / 2;        /*取得系数的个数*/
    //因为滤波数组前后的数据是相同的，所以下面这样计算可以节省一半的循环时间
    for (i = 0; i < sumnumber; i++, adtpoint++)
        adresult += ((*adtpoint) * (gu32_AdQueue[i] + gu32_AdQueue[DFNumberTab(fu32_FLevel)-1-i]));
    adresult += ((*(adtpoint)) * gu32_AdQueue[sumnumber]);
    adresult /= DEFSUMTab(fu32_FLevel);
#endif
    return(adresult);
}

/*********************************************************************
函数名称: u32 AD_GetFedVal(u32 fu32_FLevel)
功    能: 得到滤波后的AD码
说    明: 
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2013-12-10
修    改:                      时    间: 
*********************************************************************/
u32 AD_GetFedVal(u32 fu32_FLevel)
{
    ULDATA ULADVal;
    static u32 su32_AdTaskTime;
    u32 lu32_Ad;
    
    gb_AdOflFlg = false;
    
    if (gb_AdOKFlg == false)     //如果之前AD初始化不成功则重新初始化
    {
        if (gu32_Sys10ms - su32_AdTaskTime > 5)      //超过50ms初始化一次
        {
            gb_AdOKFlg = AD_Init(gs_Setup.AdSamplingRate);
            su32_AdTaskTime = gu32_Sys10ms;
        }
        gu32_AdValue = 0;
    }
    else
    {
        while(ADC_DOUT_READ)//AD未准备好
        {
            //如果超过50msAD转换还未准备好则重新初始化AD
            //120/s的AD转换速率，每次AD转换大概8.3ms，50ms时间足够AD转换完成6次了
            if (gu32_Sys10ms - su32_AdTaskTime > 5)
            {
                gb_AdOKFlg = AD_Init(gs_Setup.AdSamplingRate);
                su32_AdTaskTime = gu32_Sys10ms;
                gu32_AdValue = 0;
            }
        }
        if (ADC_DOUT_READ == 0)
        {
            su32_AdTaskTime = gu32_Sys10ms;
            ULADVal.ul = AD_ReadReg(ADCOM_KEEP);
            gu32_AdValue = ULADVal.ul >> (8+5); //获取32-(8+5)=19位AD码
        }
    }
    lu32_Ad = Ad_Filter(gu32_AdValue, fu32_FLevel);  //使用单片机版仪表的滤波算法
    gb_SigWtFlg = false;
    gb_OflFlg = false;
    if (lu32_Ad > 0x7FFC0)                   //ad转换结果过大溢出
    {
        gb_AdOflFlg = true;
        gb_OflFlg = true;
    }
    else if (lu32_Ad < 0x1F)                 //ad转换结果过小溢出
    {
        gb_AdOflFlg = true;
        gb_OflFlg = true;
        gb_SigWtFlg = true;
    }
    return lu32_Ad;
        
}

/*********************************************************************
函数名称: u32 AD_ConvertTimes(u32 fu32_SysTime)
功    能: 独立的功能函数，测试实际程序中每秒钟所能达到的AD转换次数
说    明: 查询式AD转换可以放在主循环中，中断时AD转换可放在中断中
入口参数: 系统时间，10ms
返 回 值: AD转换  次/秒
设    计: 丛海旭               时    间: 2014-2-11
修    改:                      时    间: 
*********************************************************************/
u32 AD_ConvertTimes(u32 fu32_SysTime)
{
    static u32 su32_AdTimes = 0;
    static u32 su32_TimeTemp = 0;
    static u32 su32_Result = 0;
    
    if (fu32_SysTime - su32_TimeTemp >= 100)    //1秒钟
    {    
        su32_TimeTemp = fu32_SysTime;
        su32_AdTimes++;
        su32_Result = su32_AdTimes;
        su32_AdTimes = 0;
    }
    else
        su32_AdTimes++;
    
    return su32_Result;
}


