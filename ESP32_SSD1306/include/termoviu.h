// ********************************************************************
//
//      TermoVIU
//      ==============================================
//                                  Configuration file
//      
//      
//      Version__: 0.1
//      Author___: Alexandre Pereira
//      Date_____: 30/10/2020 (Almost Pandemy Free, I hope)
//
// ********************************************************************
#ifndef Termoviu_h
#define Termoviu_h

// ********************************************************************
//             M O S T     I M P O R T A N T      I S S U E
//
//                        E M I S S I V I T Y
// ********************************************************************
// There are two ways to determine Emissivity
// If you want to use Melexis configuration, simply uncomment the USE_MELEXIS_CONFIG line ahead.
// NOTE:
// According to Melexis Application Note 0.659
// According to Testo Documentation About Humam Temperature Reading
// #define USE_MELEXIS_CONFIG 1


// ********************************************************************
// Stabilization Reading Times
// ********************************************************************
#define STABILIZATION_N_TIMES 5


// ********************************************************************
// Minimum and Maximum Valid Distance in cents of mm
// ********************************************************************
#define DISTANCE_MINIMUM 100
#define DISTANCE_MAXIMUM 250


// ********************************************************************
// Distance for message in in cents of mm
// ********************************************************************
#define DISTANCE_MESSAGE 330


// ********************************************************************
// Distance Adjust Factor 
// ********************************************************************
#ifdef USE_MELEXIS_CONFIG
#define DISTANCE_ADJ_FACTOR 0.01
#else
#define DISTANCE_ADJ_FACTOR  0.027   //0.021
#endif
  

// ********************************************************************
// Time Between Valid Readings in ms
// ********************************************************************
#define TIME_BETWEEN 50


// ********************************************************************
// Time Between Laser Sampling on Wait in ms
// ********************************************************************
#define TIME_LASER_SAMPLE 10


// ********************************************************************
// Time for Relay When Temperature is Readed in ms
// ********************************************************************
#define TIME_RELAY 1000


// ********************************************************************
// Limite da chave
// ********************************************************************
#define KEYLIMIT 1000


// ********************************************************************
// For use with Alchool Dispensers use 41, for Turnstile use 38
// ********************************************************************
#define MIN_TEMP_RELAY 41

#endif