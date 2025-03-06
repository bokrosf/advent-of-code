import 'dart:convert';
import 'dart:io';

List<int> parseNumbers(String source) {
  return RegExp(r'\d+')
    .allMatches(source)
    .map((m) => int.parse(m[0]!))
    .toList();
}

bool isValidTriangle(List<int> sides) {
  return sides[0] + sides[1] > sides[2] &&
    sides[0] + sides[2] > sides[1] &&
    sides[1] + sides[2] > sides[0];
}

void main() async {
  final lines = File('input.txt')
    .openRead()
    .transform(utf8.decoder)
    .transform(LineSplitter());

  var validCount = 0;
  final columns = [
    <int>[],
    <int>[],
    <int>[],
  ];

  await for (final l in lines) {
    final row = parseNumbers(l);

    for (int i = 0; i < row.length; ++i) {
      columns[i].add(row[i]);
    }

    if (columns.first.length == 3) {
      validCount += columns.where((c) => isValidTriangle(c)).length;
      columns.forEach((c) => c.clear());
    }
  }

  print(validCount);
}
