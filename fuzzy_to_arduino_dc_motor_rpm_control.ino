/*FUZZY LOGIC CONTROL IMPLEMENTATION ON ARDUINO
  YAHYA EKIN  03.06.2024
*/
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#define DIR1 7
#define DIR2 8
#define ENABLE 3

const uint16_t LookUpTable[61][61] PROGMEM = {
{-182, -182, -182, -182, -182, -182, -182, -182, -181, -180, -180, -179, -179, -180, -180, -181, -182, -182, -182, -181, -180, -180, -179, -178, -179, -180, -182, -182, -179, -177, -182, -177, -180, -182, -182, -172, -149, -131, -126, -125, -125, -124, -123, -123, -124, -124, -125, -125, -112, -97, -80, -54, -42, -42, -42, -42, -42, -42, -42, -42, -42},
{-182, -182, -182, -182, -182, -182, -182, -182, -181, -180, -180, -179, -179, -180, -180, -181, -182, -182, -182, -181, -180, -180, -179, -178, -179, -180, -182, -182, -179, -177, -182, -177, -180, -182, -182, -172, -149, -131, -126, -125, -125, -124, -124, -124, -124, -124, -125, -125, -112, -97, -80, -54, -42, -42, -42, -42, -42, -42, -42, -42, -42},
{-181, -181, -181, -181, -181, -181, -181, -181, -181, -173, -171, -169, -169, -171, -173, -174, -174, -174, -174, -174, -173, -171, -168, -165, -168, -173, -174, -174, -170, -153, -174, -161, -172, -174, -174, -162, -141, -124, -121, -121, -121, -121, -121, -121, -121, -121, -121, -121, -112, -97, -80, -54, -42, -42, -42, -42, -42, -42, -42, -42, -42},
{-180, -180, -180, -180, -180, -180, -180, -180, -180, -172, -156, -152, -152, -156, -159, -159, -159, -159, -159, -159, -159, -156, -152, -146, -151, -158, -159, -159, -155, -137, -159, -142, -156, -159, -159, -150, -123, -110, -109, -111, -112, -112, -112, -112, -112, -112, -112, -111, -109, -97, -80, -54, -42, -42, -42, -42, -42, -42, -42, -42, -42},
{-180, -180, -180, -180, -180, -180, -180, -180, -180, -170, -155, -144, -144, -148, -148, -148, -148, -148, -148, -148, -148, -148, -144, -139, -143, -148, -148, -148, -147, -137, -148, -138, -148, -148, -148, -142, -122, -100, -101, -104, -104, -104, -104, -104, -104, -104, -104, -104, -101, -97, -80, -55, -43, -43, -43, -43, -43, -43, -43, -43, -43},
{-179, -179, -179, -179, -179, -179, -179, -179, -179, -167, -151, -144, -140, -140, -140, -140, -140, -140, -140, -140, -140, -140, -140, -139, -140, -140, -140, -140, -140, -137, -140, -138, -140, -140, -140, -135, -121, -100, -96, -96, -96, -96, -96, -96, -96, -96, -96, -96, -96, -97, -80, -57, -43, -43, -43, -43, -43, -43, -43, -43, -43},
{-180, -180, -180, -180, -180, -180, -180, -180, -180, -170, -155, -144, -135, -133, -133, -133, -133, -133, -133, -133, -133, -133, -136, -139, -136, -133, -133, -133, -134, -137, -133, -138, -133, -133, -133, -129, -118, -100, -91, -87, -87, -87, -87, -87, -87, -87, -87, -87, -91, -97, -80, -55, -43, -43, -43, -43, -43, -43, -43, -43, -43},
{-180, -180, -180, -180, -180, -180, -180, -180, -180, -172, -155, -144, -135, -129, -128, -128, -128, -128, -128, -128, -128, -130, -131, -134, -131, -128, -128, -128, -130, -137, -128, -135, -129, -128, -128, -125, -113, -92, -81, -77, -74, -74, -74, -74, -74, -74, -74, -77, -81, -87, -80, -54, -42, -42, -42, -42, -42, -42, -42, -42, -42},
{-181, -181, -181, -181, -181, -181, -181, -181, -181, -172, -155, -144, -135, -129, -125, -125, -125, -125, -125, -125, -125, -126, -127, -129, -127, -125, -125, -125, -127, -131, -125, -130, -126, -125, -125, -122, -109, -80, -58, -55, -54, -53, -53, -53, -53, -53, -54, -55, -58, -62, -58, -54, -42, -42, -42, -42, -42, -42, -42, -42, -42},
{-182, -182, -182, -182, -182, -182, -182, -182, -181, -172, -155, -144, -135, -129, -125, -124, -124, -124, -124, -124, -125, -125, -126, -127, -126, -125, -124, -124, -126, -129, -124, -128, -125, -124, -124, -121, -108, -78, -43, -43, -42, -42, -42, -42, -42, -42, -42, -43, -43, -44, -43, -42, -42, -42, -42, -42, -42, -42, -42, -42, -42},
{-182, -182, -182, -182, -182, -182, -182, -182, -181, -172, -155, -144, -135, -129, -125, -124, -123, -123, -124, -124, -125, -125, -126, -127, -126, -125, -124, -124, -126, -129, -123, -128, -125, -124, -124, -121, -108, -78, -43, -43, -42, -42, -42, -42, -42, -42, -42, -43, -43, -44, -43, -42, -42, -42, -42, -42, -42, -42, -42, -42, -42},
{-182, -182, -182, -182, -182, -182, -182, -182, -181, -172, -155, -144, -135, -129, -125, -124, -123, -123, -124, -124, -125, -125, -126, -127, -126, -125, -124, -124, -126, -129, -123, -128, -125, -124, -124, -121, -108, -78, -43, -43, -42, -42, -42, -42, -42, -42, -42, -43, -43, -44, -43, -42, -42, -42, -42, -42, -42, -42, -42, -42, -42},
{-182, -182, -182, -182, -182, -182, -182, -182, -181, -172, -155, -144, -135, -129, -125, -124, -124, -124, -124, -124, -125, -125, -126, -127, -126, -125, -124, -124, -126, -129, -124, -128, -125, -124, -124, -121, -108, -78, -43, -43, -42, -42, -42, -42, -42, -42, -42, -43, -43, -44, -43, -42, -42, -42, -42, -42, -42, -42, -42, -42, -42},
{-180, -180, -180, -180, -180, -180, -180, -180, -180, -171, -154, -143, -135, -129, -125, -124, -124, -124, -124, -124, -124, -125, -126, -127, -126, -124, -124, -124, -125, -127, -124, -127, -125, -124, -124, -120, -107, -77, -42, -42, -42, -42, -42, -42, -42, -42, -42, -42, -42, -43, -42, -42, -42, -42, -42, -42, -42, -42, -42, -42, -42},
{-163, -163, -163, -163, -163, -163, -163, -163, -163, -153, -136, -128, -122, -118, -115, -114, -114, -114, -114, -114, -114, -114, -112, -109, -112, -114, -114, -114, -113, -98, -114, -106, -114, -114, -114, -110, -94, -62, -31, -32, -33, -33, -33, -33, -33, -33, -33, -32, -31, -29, -31, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33},
{-152, -152, -152, -152, -152, -152, -152, -152, -152, -145, -129, -117, -113, -109, -107, -106, -106, -106, -106, -106, -106, -105, -103, -99, -103, -106, -106, -106, -105, -98, -106, -97, -106, -106, -106, -103, -86, -52, -25, -26, -27, -27, -27, -27, -27, -27, -27, -26, -24, -21, -25, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27},
{-144, -144, -144, -144, -144, -144, -144, -144, -144, -138, -127, -115, -106, -103, -100, -100, -100, -100, -100, -100, -100, -100, -97, -97, -97, -100, -100, -100, -99, -98, -100, -97, -100, -100, -100, -96, -82, -49, -20, -22, -22, -22, -22, -22, -22, -22, -22, -22, -20, -20, -21, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22},
{-138, -138, -138, -138, -138, -138, -138, -138, -138, -134, -124, -115, -105, -98, -94, -94, -94, -94, -94, -94, -94, -94, -96, -97, -96, -93, -93, -93, -94, -98, -93, -97, -93, -93, -93, -90, -82, -49, -19, -18, -18, -18, -18, -18, -18, -18, -18, -18, -19, -20, -19, -18, -18, -18, -18, -18, -18, -18, -18, -18, -18},
{-134, -134, -134, -134, -134, -134, -134, -134, -134, -130, -121, -112, -103, -94, -88, -87, -87, -87, -87, -87, -87, -90, -94, -97, -94, -87, -87, -87, -90, -98, -87, -97, -89, -87, -87, -84, -81, -49, -18, -16, -15, -15, -15, -15, -15, -15, -15, -16, -18, -19, -17, -15, -15, -15, -15, -15, -15, -15, -15, -15, -15},
{-130, -130, -130, -130, -130, -130, -130, -130, -130, -127, -117, -109, -100, -90, -82, -80, -80, -80, -80, -80, -82, -85, -89, -95, -89, -82, -80, -80, -85, -97, -80, -96, -83, -80, -80, -79, -75, -49, -15, -13, -12, -11, -11, -11, -11, -11, -12, -13, -15, -18, -14, -12, -11, -11, -11, -11, -11, -11, -11, -11, -11},
{-126, -126, -126, -126, -126, -126, -126, -126, -126, -124, -115, -106, -96, -84, -75, -73, -72, -72, -72, -73, -75, -77, -82, -86, -80, -74, -71, -71, -77, -95, -71, -91, -75, -71, -71, -70, -66, -47, -10, -9, -8, -8, -7, -7, -7, -8, -8, -9, -10, -13, -10, -9, -8, -7, -7, -7, -7, -7, -7, -7, -7},
{-122, -122, -122, -122, -122, -122, -122, -122, -123, -122, -112, -103, -93, -79, -64, -61, -60, -60, -60, -61, -63, -65, -69, -70, -65, -60, -58, -58, -63, -83, -58, -74, -61, -58, -58, -56, -49, -40, -4, -3, -3, -3, -3, -3, -3, -3, -3, -3, -4, -5, -4, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3},
{-118, -118, -118, -118, -118, -118, -118, -118, -118, -119, -110, -101, -90, -76, -52, -42, -42, -42, -42, -42, -42, -43, -43, -34, -36, -37, -37, -37, -37, -27, -37, -33, -37, -37, -37, -32, -20, -3, 5, 5, 4, 4, 4, 4, 4, 4, 4, 5, 5, 7, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
{-114, -114, -114, -114, -114, -114, -114, -114, -114, -114, -110, -101, -90, -76, -52, -42, -42, -42, -42, -42, -42, -43, -43, -28, -31, -33, -33, -33, -32, -20, -33, -26, -33, -33, -33, -29, -15, 2, 9, 8, 7, 7, 7, 7, 7, 7, 7, 8, 9, 12, 9, 8, 7, 7, 7, 7, 7, 7, 7, 7, 7},
{-108, -108, -108, -108, -108, -108, -108, -108, -108, -108, -107, -101, -90, -76, -52, -42, -42, -42, -42, -42, -42, -43, -43, -27, -26, -29, -29, -29, -27, -20, -29, -20, -28, -29, -29, -25, -11, 8, 14, 12, 11, 11, 11, 11, 11, 11, 11, 12, 14, 17, 14, 12, 11, 11, 11, 11, 11, 11, 11, 11, 11},
{-100, -100, -100, -100, -100, -100, -100, -100, -100, -100, -100, -98, -90, -77, -54, -43, -43, -43, -43, -43, -43, -43, -43, -27, -21, -23, -23, -23, -22, -20, -23, -20, -23, -23, -23, -20, -8, 11, 18, 16, 16, 16, 16, 16, 16, 16, 16, 16, 18, 20, 18, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16},
{-91, -91, -91, -91, -91, -91, -91, -91, -91, -91, -91, -95, -90, -76, -54, -43, -43, -43, -43, -43, -43, -43, -43, -27, -19, -17, -17, -17, -17, -20, -17, -20, -17, -17, -17, -14, -8, 11, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 20, 20, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22},
{-79, -79, -79, -79, -79, -79, -79, -79, -79, -80, -83, -87, -87, -76, -52, -42, -42, -42, -42, -42, -42, -43, -43, -27, -14, -11, -11, -11, -13, -20, -11, -20, -12, -11, -11, -9, -3, 12, 25, 27, 28, 28, 28, 28, 28, 28, 28, 27, 25, 22, 26, 27, 28, 28, 28, 28, 28, 28, 28, 28, 28},
{-62, -62, -62, -62, -62, -62, -62, -62, -62, -64, -66, -70, -70, -66, -52, -42, -42, -42, -42, -42, -42, -43, -43, -27, -11, -5, -5, -5, -6, -17, -5, -11, -6, -5, -5, -3, 5, 18, 34, 35, 35, 35, 36, 36, 36, 35, 35, 35, 34, 32, 34, 35, 35, 36, 36, 36, 36, 36, 36, 36, 36},
{-42, -42, -42, -42, -42, -42, -42, -42, -42, -42, -43, -43, -43, -43, -42, -42, -42, -42, -42, -42, -42, -43, -43, -27, -11, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 12, 31, 43, 43, 42, 42, 42, 42, 42, 42, 42, 43, 43, 44, 43, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42},
{-42, -42, -42, -42, -42, -42, -42, -42, -42, -42, -43, -43, -43, -43, -42, -42, -42, -42, -42, -42, -42, -43, -43, -27, -11, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 12, 31, 43, 43, 42, 42, 42, 42, 42, 42, 42, 43, 43, 44, 43, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42},
{-35, -35, -35, -35, -35, -35, -35, -35, -35, -34, -34, -33, -33, -34, -34, -35, -35, -35, -35, -35, -34, -34, -33, -14, -3, 4, 5, 5, 7, 18, 5, 12, 7, 5, 5, 6, 12, 31, 43, 43, 42, 42, 42, 42, 42, 42, 42, 43, 72, 79, 72, 68, 65, 64, 63, 63, 63, 63, 63, 63, 63},
{-30, -30, -30, -30, -30, -30, -30, -30, -29, -29, -28, -26, -26, -28, -29, -29, -30, -30, -30, -29, -29, -28, -26, -8, 3, 9, 10, 10, 12, 20, 10, 20, 11, 10, 10, 11, 15, 31, 43, 43, 42, 42, 42, 42, 42, 42, 42, 43, 76, 92, 85, 81, 78, 76, 76, 76, 76, 76, 76, 76, 76},
{-25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -24, -22, -22, -24, -25, -25, -25, -25, -25, -25, -25, -24, -22, -7, 7, 12, 14, 14, 16, 20, 14, 20, 15, 14, 14, 14, 19, 31, 43, 43, 42, 42, 42, 42, 42, 42, 42, 43, 76, 96, 92, 88, 85, 85, 85, 85, 85, 85, 85, 85, 85},
{-21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -19, -19, -21, -21, -21, -21, -21, -21, -21, -21, -21, -20, -7, 10, 16, 18, 18, 18, 20, 18, 20, 18, 18, 18, 18, 20, 31, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 76, 96, 96, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93},
{-16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -18, -18, -16, -16, -16, -16, -16, -16, -16, -16, -16, -18, -7, 10, 21, 23, 23, 22, 20, 23, 20, 23, 23, 23, 23, 20, 31, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 76, 96, 98, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101},
{-11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -12, -14, -14, -12, -11, -11, -11, -11, -11, -11, -11, -12, -14, -4, 13, 26, 29, 29, 27, 20, 29, 20, 28, 29, 29, 28, 25, 31, 43, 43, 42, 42, 42, 42, 42, 42, 42, 43, 76, 96, 105, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108},
{-7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -8, -9, -9, -8, -7, -7, -7, -7, -7, -7, -7, -8, -9, 2, 17, 30, 33, 33, 32, 20, 33, 26, 33, 33, 33, 33, 30, 31, 43, 43, 42, 42, 42, 42, 42, 42, 42, 43, 76, 96, 110, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114},
{-4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -5, -5, -5, -5, -4, -4, -4, -4, -4, -4, -4, -5, -5, 7, 22, 33, 37, 37, 37, 27, 37, 33, 37, 37, 37, 37, 36, 35, 43, 43, 42, 42, 42, 42, 42, 42, 42, 43, 76, 96, 110, 119, 119, 118, 118, 118, 118, 118, 118, 118, 118},
{2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 3, 3, 3, 40, 48, 55, 57, 57, 61, 81, 56, 72, 60, 57, 57, 59, 65, 68, 67, 64, 61, 60, 59, 59, 59, 60, 62, 64, 80, 99, 112, 123, 123, 122, 122, 122, 122, 122, 122, 122, 122},
{7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 9, 10, 10, 9, 8, 7, 7, 7, 7, 7, 8, 9, 10, 58, 65, 70, 70, 70, 76, 95, 70, 90, 75, 70, 70, 73, 81, 85, 81, 76, 74, 72, 71, 71, 71, 72, 74, 77, 86, 102, 114, 125, 126, 126, 125, 125, 125, 125, 125, 125, 125},
{11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 13, 15, 14, 13, 11, 11, 11, 11, 11, 11, 12, 13, 15, 58, 75, 78, 78, 78, 85, 97, 78, 96, 83, 78, 78, 82, 90, 94, 88, 84, 81, 79, 79, 79, 79, 80, 81, 84, 93, 106, 118, 128, 130, 129, 129, 129, 129, 129, 129, 129, 129},
{14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 18, 17, 15, 14, 14, 14, 14, 14, 14, 14, 16, 18, 58, 81, 84, 85, 85, 90, 98, 85, 97, 88, 85, 85, 87, 95, 97, 93, 89, 86, 85, 85, 85, 85, 85, 86, 89, 97, 108, 121, 131, 132, 132, 132, 132, 132, 132, 132, 132, 132},
{17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 18, 19, 19, 17, 17, 17, 17, 17, 17, 17, 17, 18, 19, 58, 84, 88, 90, 90, 93, 98, 90, 97, 92, 90, 90, 90, 96, 97, 96, 92, 90, 90, 90, 90, 90, 90, 90, 92, 99, 108, 124, 134, 136, 136, 136, 136, 136, 136, 136, 136, 136},
{20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 19, 19, 20, 20, 20, 20, 20, 20, 20, 20, 20, 19, 58, 84, 93, 96, 96, 95, 98, 96, 97, 96, 96, 96, 96, 96, 97, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 99, 108, 124, 137, 141, 141, 141, 141, 141, 141, 141, 141, 141},
{23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 22, 20, 20, 22, 23, 23, 23, 23, 23, 23, 23, 22, 20, 58, 84, 98, 101, 101, 99, 98, 101, 97, 100, 101, 101, 101, 96, 97, 97, 100, 101, 101, 101, 101, 101, 101, 101, 100, 100, 108, 125, 141, 146, 146, 146, 146, 146, 146, 146, 146, 146},
{27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 26, 24, 24, 26, 27, 27, 27, 27, 27, 27, 27, 26, 24, 59, 88, 103, 106, 106, 104, 98, 106, 97, 105, 106, 106, 106, 101, 98, 102, 105, 106, 106, 106, 106, 106, 106, 106, 105, 106, 109, 125, 145, 152, 152, 152, 152, 152, 152, 152, 152, 152},
{32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 29, 30, 31, 32, 32, 32, 32, 32, 32, 32, 31, 29, 68, 93, 109, 113, 113, 111, 98, 113, 103, 112, 113, 113, 112, 109, 107, 110, 112, 112, 113, 113, 113, 113, 113, 112, 112, 114, 118, 128, 151, 161, 162, 162, 162, 162, 162, 162, 162, 162},
{39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 81, 105, 117, 121, 121, 121, 116, 121, 120, 121, 121, 121, 121, 121, 121, 122, 121, 121, 121, 121, 121, 121, 121, 121, 121, 125, 132, 145, 162, 174, 176, 176, 176, 176, 176, 176, 176, 176},
{42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 43, 43, 43, 43, 42, 42, 42, 42, 42, 42, 42, 43, 43, 86, 110, 122, 124, 124, 126, 129, 123, 128, 125, 124, 124, 125, 127, 127, 126, 125, 125, 124, 123, 123, 124, 124, 125, 125, 130, 138, 152, 172, 181, 182, 182, 182, 182, 182, 182, 182, 182},
{42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 43, 43, 43, 43, 42, 42, 42, 42, 42, 42, 42, 43, 43, 86, 110, 122, 124, 124, 126, 129, 123, 128, 125, 124, 124, 125, 127, 127, 126, 125, 125, 124, 123, 123, 124, 124, 125, 125, 130, 138, 152, 172, 181, 182, 182, 182, 182, 182, 182, 182, 182},
{42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 43, 43, 43, 43, 42, 42, 42, 42, 42, 42, 42, 43, 43, 86, 110, 122, 124, 124, 126, 129, 124, 128, 125, 124, 124, 125, 127, 127, 126, 125, 125, 124, 124, 124, 124, 124, 125, 125, 130, 138, 152, 172, 181, 182, 182, 182, 182, 182, 182, 182, 182},
{42, 42, 42, 42, 42, 42, 42, 42, 42, 54, 55, 58, 58, 55, 54, 53, 53, 53, 53, 53, 54, 56, 58, 88, 111, 122, 125, 125, 127, 131, 125, 130, 126, 125, 125, 126, 128, 129, 127, 126, 125, 125, 125, 125, 125, 125, 125, 126, 130, 138, 152, 172, 181, 181, 181, 181, 181, 181, 181, 181, 181},
{42, 42, 42, 42, 42, 42, 42, 42, 42, 56, 77, 81, 80, 76, 74, 74, 74, 74, 74, 74, 74, 77, 81, 95, 115, 125, 128, 128, 130, 137, 128, 135, 129, 128, 128, 129, 132, 133, 131, 129, 128, 128, 128, 128, 128, 128, 128, 129, 131, 138, 152, 172, 180, 180, 180, 180, 180, 180, 180, 180, 180},
{43, 43, 43, 43, 43, 43, 43, 43, 43, 57, 78, 91, 90, 87, 87, 87, 87, 87, 87, 87, 87, 87, 91, 102, 119, 130, 133, 133, 134, 137, 133, 138, 133, 133, 133, 133, 137, 139, 135, 133, 133, 133, 133, 133, 133, 133, 133, 133, 136, 139, 152, 172, 180, 180, 180, 180, 180, 180, 180, 180, 180},
{43, 43, 43, 43, 43, 43, 43, 43, 43, 60, 82, 91, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 102, 124, 136, 140, 140, 140, 137, 140, 138, 140, 140, 140, 140, 139, 139, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 139, 152, 169, 179, 179, 179, 179, 179, 179, 179, 179, 179},
{43, 43, 43, 43, 43, 43, 43, 43, 43, 57, 78, 91, 102, 104, 104, 104, 104, 104, 104, 104, 104, 104, 101, 102, 124, 143, 148, 148, 147, 137, 148, 138, 148, 148, 148, 148, 142, 139, 144, 148, 148, 148, 148, 148, 148, 148, 148, 148, 144, 139, 152, 172, 180, 180, 180, 180, 180, 180, 180, 180, 180},
{42, 42, 42, 42, 42, 42, 42, 42, 42, 56, 78, 91, 102, 111, 112, 112, 112, 112, 112, 112, 112, 111, 109, 111, 126, 153, 159, 159, 155, 137, 159, 142, 156, 159, 159, 158, 150, 146, 152, 156, 159, 159, 159, 159, 159, 159, 159, 156, 152, 146, 152, 172, 180, 180, 180, 180, 180, 180, 180, 180, 180},
{42, 42, 42, 42, 42, 42, 42, 42, 42, 56, 78, 91, 102, 112, 121, 121, 121, 121, 121, 121, 121, 121, 121, 126, 144, 165, 174, 174, 170, 153, 174, 161, 172, 174, 174, 172, 167, 165, 169, 171, 173, 174, 174, 174, 174, 174, 173, 171, 169, 165, 169, 172, 181, 181, 181, 181, 181, 181, 181, 181, 181},
{42, 42, 42, 42, 42, 42, 42, 42, 42, 56, 78, 91, 102, 112, 122, 124, 124, 124, 124, 124, 125, 125, 126, 133, 152, 174, 182, 182, 179, 177, 182, 177, 180, 182, 182, 180, 178, 178, 179, 180, 180, 181, 182, 182, 182, 181, 180, 180, 179, 178, 179, 180, 181, 182, 182, 182, 182, 182, 182, 182, 182},
{42, 42, 42, 42, 42, 42, 42, 42, 42, 56, 78, 91, 102, 112, 122, 124, 123, 123, 124, 124, 125, 125, 126, 133, 152, 174, 182, 182, 179, 177, 182, 177, 180, 182, 182, 180, 178, 178, 179, 180, 180, 181, 182, 182, 182, 181, 180, 180, 179, 178, 179, 180, 181, 182, 182, 182, 182, 182, 182, 182, 182}
};

int inputPWM[51];

unsigned long rpmtime;
float rpmfloat;
unsigned int rpm;
bool tooslow = 1;

int desired_rpm;
int rpm_error = 0;
int previous_rpm_error = 0;
int change_of_rpm_error = 0;
int drivePWM;
int rounded_x_input;
int rounded_y_input;
int Out_PWM=0;
int Previous_Out_PWM=0;

void RPM () {
  rpmtime = TCNT1;
  TCNT1 = 0;
  tooslow = 0;
}

void setup() {
  // put your setup code here, to run once:
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1 << CS12); //Prescaler 256
  TIMSK1 |= (1 << TOIE1); //enable timer overflow
  
  lcd.init();                      // initialize the lcd 
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("Fuzzy Logic");
  lcd.setCursor(0,1);
  lcd.print("Motor RPM Control");
 
  // PIN DEFINITIONS
  pinMode(2, INPUT);
  pinMode(A3, INPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(DIR2, OUTPUT);
  pinMode(ENABLE, OUTPUT);

  attachInterrupt(0, RPM, FALLING);
  Serial.begin(9600);

  digitalWrite(DIR1, LOW);
  digitalWrite(DIR2, LOW);

  for(int i = 0; i<=51; i++)
  {
    inputPWM[i] = 5*i;
  }
  Serial.println("InputPWM Array:");
  for(int i = 0; i<=51; i++)
  {
  Serial.println(inputPWM[i]);
  }
  Serial.println("-----");
  drivePWM = 0;

}

ISR(TIMER1_OVF_vect) {
  tooslow = 1;
}

void loop() {
  // put your main code here, to run repeatedly:
  int rawVal = analogRead(A3);
  //Serial.print("rawVal:");
  //Serial.println(rawVal);
  
  int desired_rpm = map(rawVal, 0, 1023, 0, 600);
  

  Serial.print("Motor_RPM:");
  Serial.print(rpm);
  Serial.print(",");

  Serial.print("Desired_RPM ");
  Serial.print(desired_rpm);
  Serial.print(",");
  
  rpm_error = desired_rpm - rpm;
  Serial.print("RPM_Error: ");
  Serial.print(rpm_error);
  Serial.print(",");

  
  change_of_rpm_error = rpm_error - previous_rpm_error;
  Serial.print("Change_of_RPM_Error: ");
  Serial.print(change_of_rpm_error);
  Serial.print(",");

  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("MO_R:");
  lcd.setCursor(5,0);
  lcd.print(rpm);
  lcd.setCursor(8,0);
  lcd.print("DE_R:");
  lcd.setCursor(13,0);
  lcd.print(desired_rpm);

  lcd.setCursor(0,1);
  lcd.print("R_Er:");
  lcd.setCursor(5,1);
  lcd.print(rpm_error);
  lcd.setCursor(8,1);
  lcd.print("C_Er:");
  lcd.setCursor(13,1);
  lcd.print(change_of_rpm_error);
  
  
  rounded_x_input  = round(rpm_error / 20.0) * 20;
  rounded_y_input  = round(change_of_rpm_error / 20.0) * 20;
  int selected_x = map(rounded_x_input, -600, 600, 0, 61);
  int selected_y = map(rounded_y_input, -600, 600, 0, 61);
  
  Out_PWM = pgm_read_word(&LookUpTable[selected_y][selected_x]);
  Serial.print(" Fuzzy_Out_PWM:");
  Serial.print(Out_PWM);
  Serial.print(",");
  
  // previous_rpm_error'i güncelle
  previous_rpm_error = rpm_error;
  
  drivePWM = Previous_Out_PWM + (Out_PWM);
  Previous_Out_PWM = drivePWM;
  
  if (Previous_Out_PWM >255 || Previous_Out_PWM<-255)
    Previous_Out_PWM = 0;
  if (drivePWM >255 || drivePWM<-255)
    drivePWM = 0; 
    
  Serial.print(" Previous_Fuzzy_Out_PWM:");
  Serial.print(Previous_Out_PWM);
  Serial.print(",");  
  Serial.print("Drive_PWM:");
  Serial.println(drivePWM); 

  if (drivePWM <0){
    digitalWrite(DIR1, LOW);
    digitalWrite(DIR2, HIGH);
    analogWrite(ENABLE, (-1*(drivePWM)));
  }
  else{
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, LOW);
    analogWrite(ENABLE, drivePWM);
  }
 
  delay(100);
  
  if (tooslow == 1) {
    Serial.print("To SLow to measure!");
  
    if (drivePWM <0){
    digitalWrite(DIR1, LOW);
    digitalWrite(DIR2, HIGH);
    analogWrite(ENABLE, (-1*(drivePWM)));
    }
    else{
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, LOW);
    analogWrite(ENABLE, drivePWM);
    }
    if (drivePWM >255 || drivePWM<-255)
    drivePWM = 0; 
    
    rpm = 0;
  }
  else {
    rpmfloat = 120 / (rpmtime/ 31250.00);
    rpm = round(rpmfloat);
    if (drivePWM >255 || drivePWM<-255)
    drivePWM = 0; 
    if (drivePWM <0)
    {
    digitalWrite(DIR1, LOW);
    digitalWrite(DIR2, HIGH);
    analogWrite(ENABLE, (-1*(drivePWM)));
    }
    else
    {
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, LOW);
    analogWrite(ENABLE, drivePWM);
    }
  }
 
  
}
