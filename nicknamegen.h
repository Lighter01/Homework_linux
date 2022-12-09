#ifndef NICKNAMEGEN_H
#define NICKNAMEGEN_H

#include "randomname.h"
#include <cwctype>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <vector>

class nng {
public:
  // Thread safe access to nickname generator singleton.
    static nng &instance() {
    static nng instance;
    return instance;
  }

  // Generates a nickname based on requested name(optional).
  std::string get_nickname(std::string name = "") const {
    return solver(name);
  };

  // Try loading every possible wordlists file from the received resource path.
  void load(const std::filesystem::path &resource_path) {
    if (std::filesystem::exists(resource_path) &&
        std::filesystem::is_directory(resource_path)) {
      for (auto &f :
           std::filesystem::recursive_directory_iterator(resource_path))
        if (f.is_regular_file() && (f.path().extension() == ".words"))
          parse_file(f);
    };
  }

private:
  // Typedef to avoid type horror when defining a container of names.
  typedef std::vector<std::string> word_container;

  // Default folder to look for wordlists resources.
  static const inline std::filesystem::path _default_resources_path{
      "./resources"};

  // Contains all vowel characters.
  static const inline std::string _vowels{
      "aeiouáàâãäåæçèéêëìíîïðñòóôõöøšùúûüýÿ"};

  // Contains all vowel characters.
  static const inline std::map<char, char> _leet_map{
      {'o', '0'}, {'O', '0'}, {'i', '1'}, {'I', '1'}, {'s', '2'}, {'S', '2'},
      {'e', '3'}, {'E', '3'}, {'a', '4'}, {'A', '4'}, {'g', '6'}, {'G', '6'},
      {'t', '7'}, {'T', '7'}, {'b', '8'}, {'B', '8'}, {'q', '9'}, {'Q', '9'}};

  // Vector for randomly accessing wordlists.
  std::vector<word_container> _wordlists;

  // Initialize random generator, no complicated processes.
  nng() { load(_default_resources_path); };

  // We don't manage any resource, all should gracefully deallocate by itself.
  ~nng(){};

  // Add an x to either the front or back of the nickname - or both.
  static std::string xfy(const std::string &nickname) {
    // Xfied nickname.
    std::string x_nickname{nickname};

    // Utilized to randomize x position.
    std::random_device random_device;

    // Distribution of possible xy, yx, xyx probability.
    std::uniform_int_distribution<std::size_t> x_distribution{0, 2};

    switch (x_distribution(random_device)) {
    case 0:
      x_nickname.push_back('X');
      break;
    case 1:
      x_nickname.insert(0, 1, 'X');
      break;
    case 2:
      x_nickname.push_back('X');
      x_nickname.insert(0, 1, 'X');
      break;
    default:
      break;
    }

    return x_nickname;
  }

  // Writes the nickname backwards such as emankcin.
  static std::string reverse(const std::string &nickname) {
    // Original nickname reversed.
    std::string reverse_nickname{nickname};

    std::reverse(std::begin(reverse_nickname), std::end(reverse_nickname));

    return reverse_nickname;
  }

  // Adds an y to the end of nickname or replace the last character if it's a
  // vowel.
  static std::string yfy(const std::string &nickname) {
    // Nickname with an y a the end.
    std::string nicknamy{nickname};

    if (std::find(std::cbegin(_vowels), std::cend(_vowels), nickname.back()) !=
        std::end(_vowels)) {
      nicknamy.back() = 'y';
    } else {
      nicknamy.push_back('y');
    }

    return nicknamy;
  }

  // Adds a number to the end of nickname.
  static std::string numify(const std::string &nickname) {
    // Nickname with an y a the end.
    std::string nickname_with_number{nickname};

    // Utilized to randomize digit added to the end of the nickname.
    std::random_device random_device;

    // Distribution of possible digits.
    std::uniform_int_distribution<std::size_t> leetify_distribution{'1', '9'};

    nickname_with_number.push_back(leetify_distribution(random_device));

    // Distribution of number of zeroes.
    std::uniform_int_distribution<std::size_t> zero_distribution{0, 3};

    // Append n zeroes to the end of the nickname.
    for (std::size_t i{0}; i < zero_distribution(random_device); i++) {
      nickname_with_number.push_back('0');
    }

    return nickname_with_number;
  }

  // Adds a trace to the end of the nickname.
  static std::string tracefy(const std::string &nickname) {
    return nickname + "-";
  }

  // Adds an ing to the end of nickname or replace the last character if it's a
  // vowel.
  static std::string ingify(const std::string &nickname) {
    // Nickname with an ing a the end.
    std::string nicknaming{nickname};

    if (std::find(std::cbegin(_vowels), std::cend(_vowels), nickname.back()) !=
        std::end(_vowels)) {
      nicknaming.back() = 'i';
      nicknaming.push_back('n');
      nicknaming.push_back('g');
    } else {
      nicknaming.push_back('i');
      nicknaming.push_back('n');
      nicknaming.push_back('g');
    }

    return nicknaming;
  }

  // Finds an aeio vowel and duplicates it, returns same nickname if no
  // available vowel.
  static std::string duovowel(const std::string &nickname) {
    static const std::string simple_vowels = "aeio";

    // Nickname with duplicated vowel.
    std::string nicknamee{nickname};

    // Try duplicating each vowel in the nickname, stop after succeeding once.
    for (const auto &vowel : simple_vowels) {
      // Iterator pointing to vowel finded in the nickname.
      const auto vowel_iterator =
          std::find(std::cbegin(nicknamee), std::cend(nicknamee), vowel);

      if (vowel_iterator != std::cend(nicknamee)) {
        nicknamee.insert(vowel_iterator, *vowel_iterator);
        break;
      }
    }

    return nicknamee;
  }

  // Replaces a letter by a numerical character.
  static std::string oneleet(const std::string &nickname) {
    // Nickname with leetified letter.
    std::string leet_nickname{nickname};

    // Candidates letter to be leetified.
    std::list<char> candidates{};

    // Retrieve candidates for replacement.
    for (auto &character : leet_nickname) {
      if (_leet_map.count(character)) {
        candidates.push_back(character);
      }
    }

    return leet_nickname;
  }

  // Replaces as much letters as possible in the nickname by numerical
  // characters.
  static std::string allleet(const std::string &nickname) {
    // Nickname leetified.
    std::string leet_nickname{nickname};

    // Replace all possible characters.
    for (auto &character : leet_nickname) {
      if (_leet_map.count(character)) {
        character = _leet_map.at(character);
      }
    }

    return leet_nickname;
  }

  // Slightly modify the nickname to add some flavor.
  static std::string leetify(const std::string &nickname, bool force = false) {
    // Utilized to randomize leetify probability content.
    std::random_device random_device;

    // Distribution of possible leetifying probability (50%).
    std::uniform_int_distribution<std::size_t> leetify_distribution{0, 1};

    // We have 1/2 chance of leetifying, force parameter overrides this.
    if (force || leetify_distribution(random_device)) {
      // When leetifying, there's 1/2 chance of using a finalizer or a random
      // leetifier.
      if (leetify_distribution(random_device)) {
        // Possible methods utilized to leetify the nickname.
        std::vector<std::function<std::string(const std::string &)>>
            possible_generators{
                reverse,  // emanckin
                duovowel, // nicknamee
                oneleet,  // n1ckname
                allleet   // n1ckn4m3
            };

        // Possible choices of leetification algorithm.
        std::uniform_int_distribution<std::size_t>
            leetify_algorithm_distribution{0, possible_generators.size() - 1};

        // New leetified nickname.
        std::string new_nickname = possible_generators.at(
            leetify_algorithm_distribution(random_device))(nickname);

        // If the new nickname didn't suffer any alteration, force leetify
        // again.
        return leetify(new_nickname, nickname == new_nickname);
      } else {
        // Possible methods utilized to leetify the nickname.
        std::vector<std::function<std::string(const std::string &)>>
            possible_generators{
                xfy,     // nicknameX
                reverse, // emanckin
                yfy,     // nicknamy
                numify,  // nickname2000
                tracefy, // nickname-
                ingify,  // nicknaming
            };

        // Possible choices of leetification algorithm.
        std::uniform_int_distribution<std::size_t>
            leetify_algorithm_distribution{0, possible_generators.size() - 1};

        // New leetified nickname.
        return possible_generators.at(
            leetify_algorithm_distribution(random_device))(nickname);
      }
    } else {
      return nickname;
    }
  };

  // Returns the nickname with an underscore separating its original parts.
  static std::string snake_case(const std::string &name) {
    // Name containing underscore.
    std::string snakefied_name{name};

    // Introduce an underscore if it's the begginning of a part of the nickname,
    // except the first.
    for (std::size_t i = 1; i < snakefied_name.size(); i++) {
      if (iswupper(snakefied_name.at(i))) {
        snakefied_name.insert(i, "_");
        i++;
      }
    }

    return snakefied_name;
  };

  // Returns the nickname in all uppercase.
  static std::string upper_case(const std::string &name) {
    // Name in all upper case characters.
    std::string upper_name{name};

    // Transform every character to uppercase if possible.
    std::for_each(
        std::begin(upper_name), std::end(upper_name),
        [](char &character) { character = std::towupper(character); });

    return upper_name;
  };

  // Returns the nickname in all lowercase.
  static std::string lower_case(const std::string &name) {
    // Name in all lower case characters.
    std::string lower_name{name};

    // Transform every character to lower if possible.
    std::for_each(
        std::begin(lower_name), std::end(lower_name),
        [](char &character) { character = std::towlower(character); });

    return lower_name;
  };

  // Returns the nickname in title case.
  static std::string title_case(const std::string &name) {
    // Well, titlecase is actually the default.
    return name;
  };

  // Returns the nickname in sentence case.
  static std::string sentence_case(const std::string &name) {
    // Sentence case formatted nickname.
    std::string sentence_name{lower_case(name)};

    // Transform the first character to upper case.
    sentence_name.at(0) = std::towupper(sentence_name.at(0));

    return sentence_name;
  };

  // Returns the nickname in camel case.
  static std::string camel_case(const std::string &name) {
    // Camel case formatted nickname.
    std::string camel_name{name};

    // Transform the first character to lower case.
    camel_name.at(0) = std::towlower(camel_name.at(0));

    return camel_name;
  };

  // Returns the nickname in reverse sentence case.
  static std::string reverse_sentence_case(const std::string &name) {
    // Reverse sentence case formatted nickname.
    std::string rsentence_name{lower_case(name)};

    // Transform the last character to upper case.
    rsentence_name.back() = std::towupper(rsentence_name.back());

    return rsentence_name;
  };

  // Returns the nickname in bathtub case.
  static std::string bathtub_case(const std::string &name) {
    // Bathtub case formatted nickname.
    std::string bathtub_name{lower_case(name)};

    // Transform the first character to upper case.
    bathtub_name.at(0) = std::towupper(bathtub_name.at(0));

    // Transform the last character to upper case.
    bathtub_name.back() = std::towupper(bathtub_name.back());

    return bathtub_name;
  };

  // Returns the nickname in winding case.
  static std::string winding_case(const std::string &name) {
    // Winding case formatted nickname.
    std::string winding_name{lower_case(name)};

    // Transform to uppercase half of the letters.
    for (std::size_t i = 0; i < winding_name.size(); i++) {
      if (!(i % 2)) {
        winding_name.at(i) = std::towupper(winding_name.at(i));
      }
    }

    return winding_name;
  };

  // Returns the nickname with case in a random fashion.
  static std::string random_case(const std::string &name) {
    // Name in all lower case characters.
    std::string random_name{lower_case(name)};

    // Utilized to randomize case.
    std::random_device random_device;

    // Distribution of possible upper or lower probability (50%).
    std::uniform_int_distribution<std::size_t> up_low_distribution(0, 1);

    // Transform every character to lower if possible.
    std::for_each(std::begin(random_name), std::end(random_name),
                  [&](char &character) {
                    if (up_low_distribution(random_device)) {
                      character = std::towupper(character);
                    }
                  });

    return random_name;
  };

  // Returns the nickname all lower case with a single random character
  // uppercase.
  static std::string random_single_case(const std::string &name) {
    // Name in all lower case characters.
    std::string random_name{lower_case(name)};

    // Utilized to randomize case.
    std::random_device random_device;

    // Distribution for name characters.
    std::uniform_int_distribution<std::size_t> character_distribution{
        0, random_name.size() - 1};

    // Position of single random character to be uppercased.
    std::size_t random_char{character_distribution(random_device)};

    random_name.at(random_char) = std::towupper(random_name.at(random_char));

    return random_name;
  };

  // Format nickname utilizing one of the possible cases.
  static std::string format(const std::string &nickname) {
    // Utilized to randomize leetify probability content.
    std::random_device random_device;

    // Chance of turning into snake case.
    std::uniform_int_distribution<std::size_t> snake_algorithm_distribution{0,
                                                                            99};

    // Nickname being randomly formatted.
    std::string formatted_nickname{nickname};

    // 1% chance of snake case. nick_name
    if (!snake_algorithm_distribution(random_device)) {
      formatted_nickname = snake_case(formatted_nickname);
    }

    // Possible methods utilized to format the nickname.
    // Repeat functions to enforce a distribution.
    std::vector<std::function<std::string(const std::string &)>>
        possible_generators = {
            upper_case,
            upper_case,
            upper_case,
            upper_case, // NICKNAME
            lower_case,
            lower_case,
            lower_case,
            lower_case,
            lower_case,
            lower_case,
            lower_case,
            lower_case, // nickname
            title_case,
            title_case, // NickName
            sentence_case,
            sentence_case,
            sentence_case,
            sentence_case,
            sentence_case, // Nickname
            camel_case,
            camel_case, // nickName
            reverse_sentence_case,
            reverse_sentence_case, // nicknamE
            bathtub_case,
            bathtub_case,
            bathtub_case,      // NicknamE
            winding_case,      // nIcKnAmE
            random_case,       // niCKnaMe
            random_single_case // nicknaMe
        };

    // Possible choices of formatting algorithm.
    std::uniform_int_distribution<std::size_t> format_algorithm_distribution{
        0, possible_generators.size() - 1};

    return possible_generators.at(format_algorithm_distribution(random_device))(
        formatted_nickname);
  };

  // Split a full name into a vector containing each name/surname.
  static std::vector<std::string> split_name(const std::string &name) {
    // Container with names/surnames split by space character.
    std::vector<std::string> splitted_name;

    // String to ease the name splitting.
    std::stringstream full_name_stream(name);

    // Single part of the full name.
    std::string single_name{""};

    while (std::getline(full_name_stream, single_name, ' ')) {
      splitted_name.push_back(single_name);
    }

    return splitted_name;
  };

  // Returns the first name.
  static std::string first_name(const std::string &name) {
    return *(split_name(name).cbegin());
  };

  // Returns the last surname.
  static std::string last_name(const std::string &name) {
    return *(split_name(name).crbegin());
  };

  // Returns any name (until it hits a space character).
  static std::string any_name(const std::string &name) {
    // Container with names/surnames that compose the received name.
    auto names_list{split_name(name)};

    // Utilized to randomize nickname content.
    std::random_device random_device;

    // Distribution of possible names.
    std::uniform_int_distribution<std::size_t> default_distribution{
        0, names_list.size() - 1};

    return names_list.at(default_distribution(random_device));
  };

  // Returns only the name initials.
  static std::string initials(const std::string &name) {
    // Generated nickname containing each name first letter.
    std::string nickname{""};

    // Container with names/surnames that compose the received name.
    auto names_list{split_name(name)};

    // Iterate through each name retrieving first letter.
    for (const auto &name : names_list) {
      nickname.push_back(*(name.cbegin()));
    }

    return nickname;
  };

  // Mix the last two names.
  static std::string mix_two(const std::string &name) {
    // Generated nickname containing a part the last two names.
    std::string nickname{""};

    // Container with names/surnames that compose the received name.
    auto names_list{split_name(name)};

    // Reduce name list to two names.
    while (names_list.size() > 2) {
      names_list.erase(names_list.begin());
    }

    // Iterate through each name retrieving random number of letters.
    for (const auto &name : names_list) {
      // Utilized to randomize nickname content.
      std::random_device random_device;

      // Distribution of possible names.
      std::uniform_int_distribution<std::size_t> normal_distribution{
          2, name.size()};

      nickname.append(name.substr(0, normal_distribution(random_device)));
    }

    return nickname;
  };

  // Mix first name with last name initial.
  static std::string first_plus_initial(const std::string &name) {
    // Container with names/surnames that compose the received name.
    auto names_list{split_name(name)};
    std::string nickname{*(names_list.cbegin()) +
                         names_list.crbegin()->front()};
    return nickname;
  }

  // Mix last name with first name initial.
  static std::string initial_plus_last(const std::string &name) {
    // Container with names/surnames that compose the received name.
    auto names_list{split_name(name)};
    std::string nickname{names_list.cbegin()->front() +
                         *(names_list.crbegin())};
    return nickname;
  }

  // Reduce a random part of the name.
  static std::string reduce_single_name(const std::string &name) {
    // Random part of name.
    std::string single_name{any_name(name)};

    if (single_name.size() > 3) {
      // Remove all vowel characters from the name unless it's already small
      // enough.
      single_name.erase(std::remove_if(single_name.begin() + 1,
                                       single_name.end() - 1,
                                       [&single_name](const char &character) {
                                         return ((_vowels.find(character) !=
                                                  std::string::npos) &&
                                                 (single_name.size() > 3));
                                       }),
                        single_name.end() - 1);
    }

    return single_name;
  }

  // Contains logic to generate a random nickname optionally based on the player
  // full name.
  std::string solver(const std::string &name) const {
    // Utilized to randomize nickname content.
    std::random_device random_device;

    // 1/4 chance of nickname being name related.
    std::uniform_int_distribution<std::size_t> default_distribution{0, 3};

    // Holds the nickname being generated.
    std::string nickname("");

    // Proceed to generate nickname based on name.
    if (_wordlists.empty() || default_distribution(random_device) == 0) {
      // Possible methods utilized to generate a nickname.
      // Purposefully adds redundancy to first and last name with any name to
      // add double weight to them.
      std::vector<std::function<std::string(const std::string &)>>
          possible_generators{
              first_name,         // John
              last_name,          // Doe
              any_name,           // Smith
              initials,           // JSD
              mix_two,            // DoSmi
              initial_plus_last,  // JSmith
              first_plus_initial, // JohnS
              reduce_single_name  // Jhn
          };

      // Possible choices of name based nickname algorithm.
      std::uniform_int_distribution<std::size_t> name_algorithm_distribution{
          0, possible_generators.size() - 1};

      // Return a nickname from one of the name based possibilities.
      nickname = possible_generators.at(name_algorithm_distribution(
          random_device))(dataspace::get_rand_name());
    }
    // Proceed to generate nickname based on a word list.
    else {
      // Distribution of possible wordlist.
      std::uniform_int_distribution<std::size_t> wordlists_range{
          0, _wordlists.size() - 1};

      // Randomly select a worldist.
      auto drawn_wordlist = _wordlists.at(wordlists_range(random_device));

      // Distribution of possible words.
      std::uniform_int_distribution<std::size_t> drawn_wordlist_range{
          0, drawn_wordlist.size() - 1};

      // Randomly selects a word from the worldist.
      nickname = drawn_wordlist.at(drawn_wordlist_range(random_device));
    }

    return format(leetify(nickname));
  };

  // Try parsing the wordlist file and index it into our container.
  void parse_file(const std::filesystem::path &file) {
    // Expected wordlist file format is content type string, list of words.
    std::ifstream tentative_file{file};

    // If managed to open the file proceed.
    if (tentative_file.is_open()) {
      // Expected delimiter character.
      const char delimiter{'\n'};

      // Line being read from the file.
      std::string file_line;

      // List of parsed words.
      word_container words_read{std::vector<std::string>()};

      // Retrieves list of words.
      while (std::getline(tentative_file, file_line, delimiter)) {
        words_read.push_back(file_line);
      }

      // Index our container.
      _wordlists.push_back(words_read);
    }
  }
};

#endif // NICKNAMEGEN_H
