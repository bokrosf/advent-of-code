import 'dart:io';

class Keypad {
  int _row = 1;
  int _column = 1;
  StringBuffer _code = StringBuffer();

  @override
  String toString() => _code.toString();

  void move(String direction) {
    final (rowDirection, columnDirection) = switch (direction) {
      'U' => (-1, 0),
      'D' => (1, 0),
      'L' => (0, -1),
      'R' => (0, 1),
      _ => throw ArgumentError.value(direction, 'direction', 'Unkown direction.')
    };

    _row = (_row + rowDirection).clamp(0, 2).toInt();
    _column = (_column + columnDirection).clamp(0, 2).toInt();
  }

  void press() {
    int key = (_row * 3) + _column + 1;
    _code.write(key);
  }
}

void main() {
  final input = File('input.txt').readAsLinesSync();
  final keypad = Keypad();

  for (final instructions in input) {
    for (int i = 0; i < instructions.length; ++i) {
      keypad.move(instructions[i]);
    }

    keypad.press();
  }

  print(keypad);
}
