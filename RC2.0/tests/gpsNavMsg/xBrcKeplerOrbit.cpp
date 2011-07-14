/*********************************************************************
*  $Id:$
*
*  Test program from June 2011.  Written to test the BrcKeplerOrbit 
*  module as it was being developed.
*
*********************************************************************/
#include <stdio.h>

#include "BrcKeplerOrbit.hpp"
#include "EngEphemeris.hpp"
#include "CivilTime.hpp"
#include "CommonTime.hpp"

using namespace std;
using namespace gpstk;

int main( int argc, char * argv[] )
{
      // Set time to Day 153, 2011 (6/2/2011) at noon
   CivilTime g( 2011, 6, 2, 12, 14, 44.0, TimeSystem::GPS );
   CommonTime dt = g.convertToCommonTime();

      // Test data (copied from navdmp output for .....)
      // Generally, we'd load these data from the file
   std::string SysID = "G";
   ObsID obsID( ObsID::otUndefined, ObsID::cbL1, ObsID::tcCA );
   short PRNID =                    3;
   double Toe =              388800.0;
   short weeknum =               1638;     // By rules of Kepler Orbit, this must be week of Toe
   double accuracy =            10.61;
   bool healthy =                true;
   double Cuc =        9.57399607E-07;
   double Cus =        8.35768878E-06;
   double Crc =        2.03562500E+02;
   double Crs =        1.87812500E+01;
   double Cic =       -2.30967999E-07;
   double Cis =        5.02914190E-08;
   double M0 =         1.05539163E+00;
   double dn =         5.39093884E-09;
   double dnDot =      0.0;                // Doesn't exist in legacy navigation message
   double ecc =        1.42575260E-02;
   double Ahalf =      5.15365528E+03; 
   double A = Ahalf * Ahalf;               // Changed from legacy navigation message
   double Adot =       0.0;                // Doesn't exist in legacy navigation message  
   double OMEGA0 =    -2.16947563E+00;
   double i0 =         9.28692498E-01;
   double w =          1.09154605E+00;
   double OMEGAdot =  -8.56285668E-09;
   double idot =       5.52880173E-10;

      //Test Data copied from RINEX file	
   double rToe =              388800.0;
   short rweeknum =               1638;     // By rules of Kepler Orbit, this must be week of Toe
   double raccuracy =            10.61;
   short raccflag =                  0;
   bool rhealthy =                true;
   short rhealth =                   0;
   short riodc =                    22;
   short rfitInt =                   0;
   short rl2pdata =                  0;
   short rcflags =                   1;
   short riode =                    22;
   long raodo =                     10;
   double rToc =              388800.0;
   short rTracker =                  1;
   double rCuc =        9.57399606705E-07;
   double rCus =        8.35768878460E-06;
   double rCrc =        2.03562500000E+02;
   double rCrs =        1.87812500000E+01;
   double rCic =       -2.30967998505E-07;
   double rCis =        5.02914190292E-08;
   double rM0 =         1.05539162795E+00;
   double rdn =         5.39093883996E-09;
   double rdnDot =      0.0;                // Doesn't exist in legacy navigation message
   double recc =        1.42575260252E-02;
   double rAhalf =      5.15365527534E+03; 
   double rA = rAhalf * rAhalf;               // Changed from legacy navigation message
   double rAdot =       0.0;                // Doesn't exist in legacy navigation message  
   double rOMEGA0 =    -2.16947563164E+00;
   double ri0 =         9.28692497530E-01;
   double rw =          1.09154604931E+00;
   double rOMEGAdot =  -8.56285667735E-09;
   double ridot =       5.52880172536E-10;
   double raf0 =        7.23189674318E-04;
   double raf1 =        5.11590769747E-12;
   double raf2 =        0.0;
   double rTgd =       -4.65661287308E-09;
  
   long subframe1[10] = { 0x22C2663D, 0x1F0E29B8, 0x2664002B, 0x09FCC1B6, 0x0F60EB8A,
                          0x1299CE93, 0x29CD3DB6, 0x0597BB0F, 0x00000B68, 0x17B28E5C };
   long subframe2[10] = { 0x22C2663D, 0x1F0E4A28, 0x05809675, 0x0EBD8AF1, 0x00089344,
                          0x008081F8, 0x1330CC2C, 0x0461E855, 0x034F8045, 0x17BB1E68 };
   long subframe3[10] = { 0x22C2663D, 0x1F0E6BA0, 0x3FE129CD, 0x26E31837, 0x0006C96A,
                          0x35A74DFC, 0x065C8B0F, 0x1E4F400A, 0x3FE8966D, 0x05860C44 };


      // First test case.  Create an empty KO object, then load the data.
   cout << "Test Case 1: Creating an empty KO object and loading the data." << endl;
   BrcKeplerOrbit ko1;
   ko1.loadData( SysID, obsID, PRNID, Toe, weeknum, accuracy, healthy, 
		 Cuc, Cus, Crc, Crs, Cic, Cis, 
		 M0, dn, dnDot, 
		 ecc, A, Ahalf, Adot, 
		 OMEGA0, i0, w, 
		 OMEGAdot, idot ); 

   Xv  xv1 = ko1.svXv( dt );
   cout.precision(11); 
   cout << "Position ko1: " << xv1.x[0] << ", " << xv1.x[1] << ", " << xv1.x[2] << ", " << endl;

      // Second test case.  Create an KO object with data available at time of construction.
   cout << endl << "Test Case 2: Creating KO object with data." << endl;
   BrcKeplerOrbit ko2( SysID, obsID, PRNID, Toe, weeknum, accuracy, healthy, 
		 Cuc, Cus, Crc, Crs, Cic, Cis, 
		 M0, dn, dnDot, 
		 ecc, A, Ahalf, Adot, 
		 OMEGA0, i0, w, 
		 OMEGAdot, idot ); 

   Xv  xv2 = ko2.svXv( dt ); 
   cout << "Position ko2: " << xv2.x << endl;
   cout << "Velocity ko2: " << xv2.v << endl;

      // Third test case.  Create a KO object using raw legacy navigation message data
   cout << endl << "Test Case 3: Creating KO object with raw legacy nav message data." << endl;
   BrcKeplerOrbit ko3(obsID, PRNID, weeknum, subframe1, subframe2, subframe3 );

   Xv  xv3 = ko3.svXv( dt ); 
   cout << "Position ko3: " << xv3.x << endl;
   cout << "Velocity ko3: " << xv3.v << endl;

      // Fourth test case.  Create a KO object using raw legacy navigation message data
   cout << endl << "Test Case 4: Creating KO object with raw legacy nav message data." << endl;
   BrcKeplerOrbit ko4;
   ko4.loadData(obsID, PRNID, weeknum, subframe1, subframe2, subframe3 );

   Xv  xv4 = ko4.svXv( dt ); 
   cout << "Position ko4: " << xv4.x << endl;
   cout << "Velocity ko4: " << xv4.v << endl;
   double RelCorr = ko4.svRelativity( dt ); 
   cout << "RelCorr ko4: " << RelCorr<< endl;

      // Fifth test case.  Create an KO object with data available from RINEX file.
   cout << endl << "Test Case 5: Creating KO object with data from RINEX file." << endl;
   BrcKeplerOrbit ko5( SysID, obsID, PRNID, rToe, rweeknum, raccuracy, rhealthy, 
		 rCuc, rCus, rCrc, rCrs, rCic, rCis, 
		 rM0, rdn, rdnDot, 
		 recc, rA, rAhalf, rAdot, 
		 rOMEGA0, ri0, rw, 
		 rOMEGAdot, ridot ); 

   Xv  xv5 = ko5.svXv( dt ); 
   cout << "Position ko5: " << xv5.x << endl;
   cout << "Velocity ko5: " << xv5.v << endl;

      // Sixth test case.  Compare against "classic" EngEphemeris
   cout << endl << "Test Case 6: Calculated position using 'classic' EngEphemeris." << endl;
   cout<< "Time= "<< g << endl;
   EngEphemeris EE;
   EE.addSubframe(subframe1, weeknum, 3, 1);
   EE.addSubframe(subframe2, weeknum, 3, 1);
   EE.addSubframe(subframe3, weeknum, 3, 1);

  // cout<<"dump above Xvt: "<<endl;
  // cout<<EE<<endl;
   Xvt xvt = EE.svXvt(dt);
   cout<< "Position EE: " << xvt.x <<endl;
   cout<< "Velocity EE: " << xvt.v <<endl;
   cout<< "RelCorr EE:  " << EE.svRelativity(dt) <<endl;

      // Test data (copied from navdmp output for PRN 6 Day 155, 2011)
   long subframeA1[10] = { 0x22C2663D, 0x30A2291C, 0x2664002B, 0x0DB9B68A, 0x12746316,
                           0x0BAC1EAA, 0x0DA73D35, 0x1A80002C, 0x00000574, 0x02C3A0F4 };
   long subframeA2[10] = { 0x22C2663D, 0x30A24A8C, 0x1A80864C, 0x0C15B3B1, 0x0AD1AB66,
                           0x00B00201, 0x3A1D9937, 0x00F6A87A, 0x0353C6C1, 0x00001F0C };
   long subframeA3[10] = { 0x22C2663D, 0x30A26B04, 0x3FDF944D, 0x2E5CB356, 0x002FCA3A,
                           0x040A9DDC, 0x0B45D00B, 0x03922318, 0x3FE905EF, 0x1A817FAC };

   CivilTime ct2(2011, 6, 4, 11, 30, 0.0, TimeSystem::GPS );
   dt = ct2.convertToCommonTime( );
   cout << endl << "Test Case 7: Calculated position using 'classic' EngEphemeris." << endl;
   cout << "Time = " << ct2 << endl;
   EngEphemeris EEA;
   EEA.addSubframe(subframeA1, weeknum, 9, 1);
   EEA.addSubframe(subframeA2, weeknum, 9, 1);
   EEA.addSubframe(subframeA3, weeknum, 9, 1);

   xvt = EEA.svXvt(dt);
   cout<< "Position EE: " << xvt.x <<endl;
   cout<< "Velocity EE: " << xvt.v <<endl;
   cout<< "Relativity : " << EE.svRelativity( dt ) << endl; 


   CivilTime ct3(2011, 6, 5, 1, 0, 0.0, TimeSystem::GPS );
   dt = ct3.convertToCommonTime( );
   cout << endl << "Test Case 8: Calculated position using 'classic' EngEphemeris." << endl;
   cout << "Time = " << ct3 << endl;

   xvt = EEA.svXvt(dt);
   cout<< "Position EE: " << xvt.x <<endl;
   cout<< "Velocity EE: " << xvt.v <<endl;
   cout<< "Relativity : " << EE.svRelativity( dt ) << endl; 

   //Ninth test case. load setSubframe() methods from EngEphemeris
   cout << endl << "Test Case 9: loading setSubframe methods from EngEphemeris." << endl;
   EngEphemeris EEload;

   unsigned short tlm[3] = { 0x008B,
                             0x008B,
                             0x008B};
   long how[3] = { 381606,
                   381612,
                   381618};
   short asalert[3] = {1,1,1};
   EEload.loadData( SysID, tlm, how, asalert,
                    rTracker, PRNID, 
                    rweeknum, rcflags, raccflag, 
                    rhealth, riodc, rl2pdata,
                    raodo,  rTgd, rToc,
                    raf2,  raf1, raf0,
                    riode, rCrs, rdn,
                    rM0,  rCuc, recc,
                    rCus, rAhalf, rToe,
                    rfitInt, rCic, rOMEGA0,
                    rCis, ri0, rCrc,
                    rw,  rOMEGAdot, ridot); 

   //Tenth test case. load seSF methods from EngEphemeris
   cout << endl << "Test Case 10: loading setSF methods from EngEphemeris." << endl;
   EngEphemeris ESFload;

   unsigned tlm1 = 0x008B;
   double how1 = 381606;
   double how2 = 381612;
   double how3 = 381618;
   short asalert1 = 1;
   cout<< "Before ESF1load.setSF1" << endl;

   ESFload.setSF1( tlm1,  how1, asalert1, 
                                       rweeknum, rcflags, raccflag, 
                                       rhealth, riodc, rl2pdata,
                                       rTgd, rToc, raf2,
                                       raf1, raf0, rTracker, 
                                       PRNID );
   cout << "Before ESF2load.setSF2" << endl;


   ESFload.setSF2( tlm1, how2, asalert1,
                                       riode, rCrs, rdn, 
                                       rM0, rCuc, recc, 
                                       rCus, rAhalf, rToe, 
                                       rfitInt );
   cout << "Before ESF3load.setSF3 " << endl;
   ESFload.setSF3( tlm1, how3, asalert1,
                                       rCic, rOMEGA0, rCis, 
                                       ri0, rCrc, rw, 
                                       rOMEGAdot, ridot );

   cout << endl << "dump output for Test Cases 4,6, and 9." << endl;
   
   cout << "EE dump: " << endl;
   cout << EE << endl;

   cout << "ko4 dump: "<< endl;
   cout << ko4 << endl;

   cout << "setSubframe methods: " << endl;
   cout << EEload << endl;

   cout << "SF1,2, and 3 methods: " << endl;
   cout << ESFload << endl;

   cout << EEA<< endl;

   return(0);
}