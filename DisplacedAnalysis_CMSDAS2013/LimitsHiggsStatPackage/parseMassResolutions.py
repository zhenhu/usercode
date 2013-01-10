#!/usr/bin/python
################################################################
# Parse file containing mass resolution numbers
################################################################

import sys

def parseMassResolutions(fileName, MH, MX, expectedNum):

    # Map for returned vectors for returned resolutions as a function of lifetime for electrons/muons
    res = {}

    # Vectors of resolutions as a function of lifetime.
    resE  = []
    resMu = []

    # Must add leading zero to MX, since expected by file.
    if int(MX) < 100:
        MX = '0%s' %(MX)

    seekName = "%s_%s" %(MH, MX)

    file = open(fileName, "r")

    foundSec = False
    nfound = -1
    for line in file:
        line = line.replace('\t',' ') # get rid of tabs, if present.
        line = line.replace('\n','')  # get rid of new line, if present.
        words = line.split(' ')
        if foundSec:
            if len(line) > 0:
                nfound += 1
                # First line just contains column headings.
                if nfound > 0:
                    try:
                        # Get mass resolutions
                        resE.append ( float(words[4]) )
                        resMu.append( float(words[2]) )
                        # print nfound, resE[-1], resMu[-1]
                    except:
                        # error
                        print words[4]
                        sys.exit("File %s has unexpected line %s"  %(fileName, line) )
            else:
                # end of section
                break                
        else:
            if words[0] == seekName:
                # Found section containing requested masses.
                foundSec = True
    file.close()

    res["Electrons"] = resE
    res["Muons"]     = resMu

    if nfound != expectedNum:
        sys.exit("Wrong number of lifetimes in file %s %i/%i" %(fileName, nfound, expectedNum) )

    return res 

