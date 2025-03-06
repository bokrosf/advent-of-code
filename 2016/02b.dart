import 'dart:io';

class Keypad {
  int _row = 2;
  int _column = 0;
  StringBuffer _code = StringBuffer();
  final _layout = [
    '  1  ',
    ' 234 ',
    '56789',
    ' ABC ',
    '  D  ',
  ];

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

    final newRow = (_row + rowDirection).clamp(0, 4).toInt();
    final newColumn = (_column + columnDirection).clamp(0, 4).toInt();
    
    if (_layout[newRow][newColumn] != ' ') {
      _row = newRow;
      _column = newColumn;
    }
  }

  void press() {
    _code.write(_layout[_row][_column]);
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
