# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.HMMLIB.Debug:
/Users/thorjakobsen/GIT/elastical-testical/hmmmmlib/build/Debug/HMMLIB:
	/bin/rm -f /Users/thorjakobsen/GIT/elastical-testical/hmmmmlib/build/Debug/HMMLIB


PostBuild.HMMLIB.Release:
/Users/thorjakobsen/GIT/elastical-testical/hmmmmlib/build/Release/HMMLIB:
	/bin/rm -f /Users/thorjakobsen/GIT/elastical-testical/hmmmmlib/build/Release/HMMLIB


PostBuild.HMMLIB.MinSizeRel:
/Users/thorjakobsen/GIT/elastical-testical/hmmmmlib/build/MinSizeRel/HMMLIB:
	/bin/rm -f /Users/thorjakobsen/GIT/elastical-testical/hmmmmlib/build/MinSizeRel/HMMLIB


PostBuild.HMMLIB.RelWithDebInfo:
/Users/thorjakobsen/GIT/elastical-testical/hmmmmlib/build/RelWithDebInfo/HMMLIB:
	/bin/rm -f /Users/thorjakobsen/GIT/elastical-testical/hmmmmlib/build/RelWithDebInfo/HMMLIB




# For each target create a dummy ruleso the target does not have to exist
