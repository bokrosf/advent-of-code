import 'dart:convert';
import 'dart:io';

bool containsAbba(String text) {
  var contains = false;

  for (int i = 0; i < text.length - 3 && !contains; ++i) {
    contains = text[i] != text[i + 1] &&
      text[i] == text[i + 3] &&
      text[i + 1] == text[i + 2];
  }

  return contains;
}

void main() async {
  final lines = File('input.txt')
    .openRead()
    .transform(utf8.decoder)
    .transform(LineSplitter());

  var tlsSupportCount = 0;

  await for (final ip in lines) {
    final hypernet = RegExp(r'\[[a-z]*\]');

    if (hypernet.allMatches(ip).any((m) => containsAbba(m[0]!))) {
      continue;
    }

    if (ip.split(hypernet).any((part) => containsAbba(part))) {
      ++tlsSupportCount;
    }
  }

  print(tlsSupportCount);
}
