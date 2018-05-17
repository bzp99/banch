#
# Ehhez hasonlo makefile fut a JPORTA-n
#
# Masolja be a jportara feltoldendo fajlait ebbe a katalogisba (2 db zip, és egy text)
#
# Zipek kicsomagolasa: 
#    make unpack
# 
# forditas address sanitizer-rel:
#    make 
#
# forditas MEMTRACE-szel:
#    make CHK=MEMTRACE
#
# futtatas:
#    ./exe
# vagy:
#    ./exe < standard_inputhoz_feltoltott_text_file
#
#
CC=g++
SRC_EXTS=cpp cc
HDR_EXTS=h hpp
ZIP_EXTS=zip

ifeq ($(CHK),MEMTRACE)
## Memtrace-hez
  CFLAGS= -ggdb -Wall -Werror -DMEMTRACE -DCPORTA -std=c++11
  LDFLAGS=
else
## Address sanitzer-hez
  CFLAGS= -ggdb -fsanitize=address -fno-omit-frame-pointer -Wall -Werror -Wno-sign-compare -DCPORTA -std=c++11
  LDFLAGS=-lasan
endif

EXECUTABLE=exe
DIRS=$(wildcard */.)
SOURCES=$(foreach ext,$(SRC_EXTS),$(wildcard *.$(ext)))
HEADERS=$(foreach ext,$(HDR_EXTS),$(wildcard *.$(ext)))
ZIP=$(foreach ext,$(ZIP_EXTS),$(wildcard *.$(ext)))
OBJECTS=$(addsuffix .o, $(basename $(SOURCES)))
SRC1=$(shell echo $(SOURCES) | tr -dc '[:print:]')
HDR1=$(shell echo $(HEADERS) | tr -dc '[:print:]')
NUMFILES=$(shell ls * | wc -l)
NUMWORDS=$(shell ls * | wc -w) 
FILETYPES=$(shell file $(SOURCES) $(HEADERS))

.PHONY: all
all: $(EXECUTABLE)

.PHONY: compile
compile: clean $(OBJECTS)

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE): clean chkdir chkfile $(SOURCES) $(OBJECTS)
ifneq ($(strip $(LDFLAGS)),-c)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)
endif

unpack:
	echo $(ZIP)
	for i in $(ZIP); do unzip -n $$i; done
	
.PHONY: chkdir
chkdir:
ifneq ($(strip $(DIRS)),)
	@echo "Subdirectory detected in zip file (src). Stop." 1>&2
	@exit 1
endif

.PHONY: chkfile
chkfile:
ifneq ($(strip $(NUMFILES)), $(strip $(NUMWORDS)))
	@echo "Szokoz a fajlnevben!"
	exit 1
endif
ifneq ($(strip $(SOURCES)),$(strip $(SRC1)))
	@echo "Nem ASCII karakterek a fajlnevben!"
	@echo ".$(SOURCES)."
	@echo ".$(SRC1)."
	@exit 1
endif
ifneq ($(strip $(HEADERS)),$(strip $(HDR1)))
	@echo "Nem ASCII karakterek a fajlnevben!"
	@echo ":$(HEADERS):"
	@echo ":$(HDR1):"
	@exit 1
endif
ifneq (,$(findstring UTF-16, $(FILETYPES)))
	@echo "UTF-16 kodolasu forras:"
	@file $(SOURCES) $(HEADERS) | grep UTF-16
	@exit 1
endif

define rulegen
%.o: %.$(1)
	$$(CC) $$(CFLAGS) -c $$< -o $$@
endef

$(foreach ext,$(SRC_EXTS),$(eval $(call rulegen,$(ext))))

# disable implicit rules
.SUFFIXES:

