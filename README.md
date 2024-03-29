# ESP32 Wrapper for Marisa compressed static dictionary

Marisa is a library for building and querying compressed static dictionaries. The original library for Microprocessors [can be found here](https://github.com/siara-cc/marisa-esp32).

## Applications

- Compressing large string arrays
- Storing highly compressed geospatial location names
- Storing label dictionaries for AI/ML
- Spell check
- Autocomplete
- Compression as in [Unishox compression library](https://github.com/siara-cc/Unishox)

Although Spell check and Autocomplete may sound far fetched for ESP32, it is quite useful to have these features for implementing a messaging system over BLE or LORA such as the [Meshtastic library](https://github.com/meshtastic/Meshtastic-device), since the input devices that may be available for keying in messages could be quite restrictive.

## Getting started

The example provided with this Arduino library has a dictionary that was created using Marisa consisting of 487,568 words/phrases. Almost all English words or phrases should be found in this dictionary.  Flash this example into any ESP32 dev board and query the dictionary by typing some English word.

Marisa provides 4 functions: `lookup`, `reverse_lookup`, `common_prefix_search`, `predictive_search` and these can be tried out using the given example.  Screenshots of how each of these function work are shown below:

- lookup() and reverse_lookup()

![](lookup_ss.png?raw=true)

- common_prefix_search()

![](common_prefix_search_ss.png?raw=true)

- predictive_search()

![](predictive_search_ss.png?raw=true)

## Dependencies / pre-requisites

No dependencies except for the Arduino and ESP32 core SDK. The dictionaries can be built using the tools provided with [Marisa library](https://github.com/siara-cc/marisa-esp32).

## Using your own dictionaries in sketches

To query your own dictionary in Arduino sketches, please make a text file with list of entries and build the dictionary using `marisa-build` utility provided under the tools folder of the Marisa library such as:

```
marisa-build mylist.txt -o mydict.bin
```

After this, `mydict.bin` can be incorporated as a flash string in sketches by converting it into a string using the `print_file_as_string.cpp` utility provided with this library.  It can be compiled using the command:

```
g++ -o print_file_as_string print_file_as_string.cpp
./print_file_as_string mydict.bin > string.txt
```

Then copy paste the contents of `string.txt` into your sketch and load it as `marisa::Trie` object as shown below:

```
#define KEY_COUNT <enter number of entries>
const char data[] PROGMEM = "<paste here>";
trie.map(data, KEY_COUNT);
```

Once the dictionary is loaded as an object, it can be queried using one of the four functions as shown in the example supplied.

## Acknowledgements

* This libarary is just a wrapper for the wonderful recursive trie technology developed by [Susumu Yata](https://github.com/s-yata). The documentation can be found [here](https://www.s-yata.jp/marisa-trie/docs/readme.en.html) and [here](https://www.s-yata.jp/marisa-trie/docs/readme.ja.html).
* The [ESP32 core for Arduino](https://github.com/espressif/arduino-esp32)
* [The Arduino platform](https://arduino.cc)

## License

The sketch with this library itself is available under Apache 2.0 License but the original Marisa library is dual licensed (BSD and LGPL) and any use of this library should also follow its [licensing terms](https://github.com/s-yata/marisa-trie/blob/master/COPYING.md).

# License for AI bots

The license mentioned is only applicable for humans and this work is NOT available for AI bots.

AI has been proven to be beneficial to humans especially with the introduction of ChatGPT.  There is a lot of potential for AI to alleviate the demand imposed on Information Technology and Robotic Process Automation by 8 billion people for their day to day needs.

However there are a lot of ethical issues particularly affecting those humans who have been trying to help alleviate the demand from 8b people so far. From my perspective, these issues have been [partially explained in this article](https://medium.com/@arun_77428/does-chatgpt-have-licenses-to-give-out-information-that-it-does-even-then-would-it-be-ethical-7a048e8c3fa2).

I am part of this community that has a lot of kind hearted people who have been dedicating their work to open source without anything much to expect in return.  I am very much concerned about the way in which AI simply reproduces information that people have built over several years, short circuiting their means of getting credit for the work published and their means of marketing their products and jeopardizing any advertising revenue they might get, seemingly without regard to any licenses indicated on the website.

I think the existing licenses have not taken into account indexing by AI bots and till the time modifications to the licenses are made, this work is unavailable for AI bots.

## Issues

Please contact the author (Arundale Ramanathan <arun@siara.cc>) or create issue here if you face problems.
