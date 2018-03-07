# Wishlist

for lack of a better title :)

## Codestyle

### Whitespace

The general coding guidelines sound nice; but perhaps indicate a
preferred level of indentation in case a new file is created or an old
one is cleaned up (e.g. due to mixed styles) or rewritten.

### bool

Avoid using bool parameters; they are hard to read.  Use enum class
instead.

### default parameters

Avoid default parameters; they are hard to read.

## Data handling

Currently the classes derived from `DNSRecordContent` sometimes use the
zone representation to store data (`TXT` (#6010), DNS names), and
sometimes they actually parse it (integers, timestamps, blobs).

They should always use a normalized representation:

- ideally serializing to wire shouldn't fail if parsing the text was
  successful
- it shouldn't matter whether data was serialized to wire and
  deserialized back before creating the text representation: it should
  always return a normalized ("canonical") representation (#2429, #3511)
- the zone parse API could probably use a separate "logger" to report
  lints on the zone representation; comparing with the canonical
  representation is not a good way to detect "bad" representations.
- trailing dots are avoided in storage, I'm guessing this is the reason
  (#5144, #5215).  I'd actually like to see trailing dots in storage...
- `DNSResourceRecord::{setContent,getZoneRepresentation}` are completely
  undocumented, and look like horrible code trying to fix problems based
  on this.

## Buildsystem

### Generic

The symlinks confuse the hell out of all IDEs I tried so far.

The files should instead be sorted into directories depending on what
needs them, e.g:

- a `common/` directory for files shared between all targets
- for each target (`pdns`, `(pdns-)recursor`, `dnsdist`) a directory
  containing files used by only the target
- if really needed special `common_*` directories for files shared by
  multiple but not all targets.

That way it is immediately clear which targets are affected by a change
(i.e. which unit tests to run).

`configure.ac` would then scan for the presence of the target
directories to determine which targets are available.

    # configure.ac
    AC_SUBST([ENABLED_TARGETS])

    m4_syscmd([test -d "dnsdist"])
    m4_if(m4_sysval, [0], [
        AC_CONFIG_FILES([dnsdist/Makefile])

        AC_ARG_ENABLE([dnsdist], ...)
        if test "$dnsdist_enabled" = "yes"; then
            ENABLED_TARGETS="$ENABLED_TARGETS dnsdist"
        fi
    ])

    # customize name/version if only one target is enabled for make dist.
    case "$ENABLED_TARGETS" in
    " dnsdist")
        PACKAGE="dnsdist"
        VERSION="..."
        ;;
    esac

    # Makefile.am
    SUBDIRS = $(ENABLED_TARGETS)

Not enabled targets are excluded by `make dist` too.

### Offline

Neither `configure` nor `make` should fetch dependencies over the
network by default.  The configure options should explicitly mention
they require/use network resources.
