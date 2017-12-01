# ANSI terminal format code generator
Run time library to generate ANSI terminal format codes for the purpose of generated formatted text within a supporting terminal's output. Support for black, blue, cyan, green, grey, magenta, red, white, and yellow colored foreground text and background are supported. Additionally, text may be specified to have blink, bold, dim, hidden, inverted, light, and underlined format modifiers.

The code generates the necessay prefix to be inserted in prior to the desired formatted content, and the necessary format suffix to reset the ouputting. Format modifiers may be used in any combination, only one foreground, and only one background color are supported at a time. Specifying more than foreground or background color will have undefined behavior.

A string string containing format descriptors is parsed using:

````cpp
ctrm::format_code(string)
````

which will return the necessary format prefix.

Format reset codes are less thoroughly supported by:

````cpp
ctrm::reset(unsigned char c = '\0')
````

Without manual specification of c, the function will default to reset all formatting. Alternatively, a single format modifier may be reset by specifying the format modifier by format code.

See ansi_term.hpp for format codes (subject to change). As of writing:

## Color
Use upper case for background, lowercase for foreground
* Black 'K'
* Blue 'B'
* Cyan 'C'
* Green 'G'
* Grey, Dark 'D'
* Grey, Light 'L'
* Magenta 'M'
* Red 'R'
* White 'W'
* Yellow 'Y'

## Format Modifiers
* Blink '%'
* Bold '#'
* Dim '$'
* Hidden '*'
* Inverted '!'
* Light '^'
* Underlined '_'

## Addition notes:
- Unless dynamic behavior is deeply needed, generating the necessary codes once, then caching the results is recommended.
- Rebinding the format codes may be achieved by editing only the headder and recompiling.
