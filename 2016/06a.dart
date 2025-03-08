import 'dart:convert';
import 'dart:io';

final frequencies = List<Map<String, int>>.generate(8, (i) => <String, int>{});

void countCharacterFrequencies(String text) {
  for (int i = 0; i < text.length; ++i) {
    final key = text[i];
    final mapping = frequencies[i];

    if (mapping.containsKey(key)) {
      mapping[key] = mapping[key]! + 1;
    } else {
      mapping[key] = 0;
    }
  }
}

String mostFrequentCharacter(Map<String, int> frequencies) {
  return frequencies.entries.reduce((a, b) => b.value > a.value ? b : a).key;
}

void main() async {
  final lines = File('input.txt')
    .openRead()
    .transform(utf8.decoder)
    .transform(LineSplitter());

  await for (final l in lines) {
    countCharacterFrequencies(l);
  }

  final message = StringBuffer();

  for (final f in frequencies) {
    message.write(mostFrequentCharacter(f));
  }

  print(message);
}
