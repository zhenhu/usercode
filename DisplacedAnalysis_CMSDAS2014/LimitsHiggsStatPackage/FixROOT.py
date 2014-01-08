#-- This file seems necessary to allow one to do things in python like
#-- workspace.Import(data, Rename("myData"))
# Author: Jan Veverka

import re
import sys
import ROOT as r

def usingNamespaceRooFit():
    return

# Since "import" clashes with python command, define RooWorkSpace.Import() instead.
setattr(r.RooWorkspace, "Import", getattr(r.RooWorkspace, "import"))

### Define all the callable attributes of r.RooFit -------------------------
_titlePattern = re.compile("^[A-Z]")
for method in dir(r.RooFit):
    if callable(getattr(r.RooFit, method)) and re.search(_titlePattern, method):
        if method in vars():
            print "% not imported since it already exists!" % method
        else:
            setattr(sys.modules[__name__], method, getattr(r.RooFit, method))
