import 'dart:convert';
import 'dart:io';

typedef Triangle = ({int a, int b, int c});

Triangle parseTriangle(String source) {
  final pattern = RegExp(r'\d+');
  final matches = pattern.allMatches(source).toList();

  return (
    a: int.parse(matches[0][0]!),
    b: int.parse(matches[1][0]!),
    c: int.parse(matches[2][0]!),
  );
}

bool isValid(Triangle t) {
  return t.a + t.b > t.c &&
    t.a + t.c > t.b &&
    t.b + t.c > t.a;
}

void main() async {
  final lines = File('input.txt')
    .openRead()
    .transform(utf8.decoder)
    .transform(LineSplitter());

  int validCount = 0;

  await for (final l in lines) {
    if (isValid(parseTriangle(l))) {
      ++validCount;
    }
  }

  print(validCount);
}
