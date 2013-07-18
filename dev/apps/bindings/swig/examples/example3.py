"""
A GPSTk example featuring more complex processing. You can use the
sample text file rinex3obs_data.txt. A PRN number that gives useful output is 5.

This is a port of the older C++ example3.cpp.

Usage:

  python example3.py <rinex3obs_filename>

For example:
  python example3.py rinex3obs_data.txt

"""


import gpstk
from gpstk.constants import *
import sys

# We recommend only using
#     'import gpstk',
# but if you need constants fairly often, then importing them all can be useful.


def main(args=sys.argv):
    if len(args) < 2:
        print 'This programs requires an argument that is a RINEX Obs file.'
        sys.exit()

    file_name = args[1]
    user_input = raw_input('Name your PRN of interest, by number: 1 through 32: ')
    int_prn = int(user_input)

    #  You could also find this value from: gpstk.constants.GAMMA_GPS, or just GAMMA_GPS
    gamma = (L1_FREQ_GPS / L2_FREQ_GPS)**2

    try:
        print 'Reading ' + file_name + '.'
        header, data = gpstk.readRinex3Obs(file_name)  # read in everything
        print header

        indexP1 = header.getObsIndex('P1')
        indexP2 = header.getObsIndex('P2')

        # Now we loop through all the epochs and process the data for each one
        for d in data:
            # Let's use the CivilTime class to print an easy to understand time:
            civtime = gpstk.CivilTime(d.time)
            print civtime,

            # Make a GPSTk SatID for the user's PRN so we can search for it
            prn = gpstk.RinexSatID(int_prn, gpstk.SatID.systemGPS)

            # Check if the PRN is in view (by searching for it)
            if d.obs.find(prn) == d.obs.end():
                print 'PRN', int_prn, 'not in view'

            else:
                P1 = d.getObs(prn, "P1", header).data
                P2 = d.getObs(prn, "P2", header).data
                L1 = d.getObs(prn, "L1", header).data
                mu = P1 - L1*(C_MPS/L1_FREQ_GPS) - 2*(P1-P2)/(1-gamma)
                print 'PRN', int_prn, 'biased multipath', mu

    # We can catch any custom gpstk exception like this:
    except gpstk.exceptions.Exception as e:
        print e


if __name__ == '__main__':
    main()
