# FluteFingers

Convert musical notes into recorder fingerings. You can import a
Capella 10 or MusicXML file, and FluteFingers will try to read the
document and give you a rendered document containing the musical
notes as well as the graphical recorder fingerings above each note.

The implementation is still work in progress.

## Code architecture (top down)

* User Frontends
  * `ui`: WinForms-based UI written in C#
  * I also plan to somehow release this for tablets & smartphones. Stay tuned!
* `core-clrbridge`: C++/CLR project that acts as a glue between core logic
  and .NET assemblies
* `core`: library written C++ containing logic for reading the various
  file formats (at the moment MusicXML, CapXML 10)
* `core-tests`: Microsoft CppUnitTest based test suite for `core`