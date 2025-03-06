import 'dart:convert';
import 'dart:io';

typedef Room = ({
  String name,
  String rawName,
  int sector,
  String checksum,
});

Room parseRoom(String source) {
  final pattern = RegExp(r'(?<name>[a-z-]+)-(?<sector>\d+)\[(?<checksum>[a-z]+)\]');
  final match = pattern.firstMatch(source)!;
  final name = match.namedGroup('name')!;

  return (
    name: name.replaceAll('-', ''),
    rawName: name,
    sector: int.parse(match.namedGroup('sector')!),
    checksum: match.namedGroup('checksum')!,
  );
}

List<({String letter, int count})> mostCommonLetters(String text) {
  final letterCounts = <String, int>{};

  for (int i = 0; i < text.length; ++i) {
    final letter = text[i];

    if (letterCounts.containsKey(letter)) {
      letterCounts[letter] = letterCounts[letter]! + 1;
    } else {
      letterCounts[letter] = 1;
    }
  }

  final sortedLetters = <({String letter, int count})>[];
  letterCounts.forEach((k, v) => sortedLetters.add((letter: k, count: v)));

  sortedLetters.sort((a, b) {
    int countOrder = -a.count.compareTo(b.count);

    return countOrder == 0
      ? a.letter.compareTo(b.letter)
      : countOrder;
  });

  return sortedLetters;
}

bool isRealRoom(Room room) {
  final letterCounts = mostCommonLetters(room.name);

  for (int i = 0; i < room.checksum.length; ++i) {
    if (letterCounts[i].letter != room.checksum[i]) {
      return false;
    }
  }

  return true;
}

String decryptRoomName(Room room) {
  final firstLetterCode = 'a'.codeUnitAt(0);
  final alphabetLetterCount = 'za'.codeUnits.reduce((v, e) => v - e) + 1;
  final decyphered = StringBuffer();

  for (int i = 0; i < room.rawName.length; ++i) {
    if (room.rawName[i] == '-') {
      decyphered.write(' ');
    } else {
      var offset = room.rawName[i].codeUnitAt(0) - firstLetterCode + room.sector;
      offset %= alphabetLetterCount;
      decyphered.writeCharCode(firstLetterCode + offset);
    }
  }

  return decyphered.toString();
}

void main() async {
  final rooms = File('input.txt')
    .openRead()
    .transform(utf8.decoder)
    .transform(LineSplitter())
    .map(parseRoom);

  await for (final r in rooms.where(isRealRoom)) {
    print('${decryptRoomName(r)}: ${r.sector}');
  }
}
