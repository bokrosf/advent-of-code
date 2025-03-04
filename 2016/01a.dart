import 'dart:io';

enum Rotation { left, right }

(Rotation rotation, int blocks) parse(String instruction) {
  int blocks = int.parse(instruction.substring(1));

  return switch (instruction[0]) {
    'L' => (Rotation.left, blocks),
    'R' => (Rotation.right, blocks),
    _ => throw FormatException("Unknown direction type.", instruction[0])
  };
}

class Vector2 {
  final int x;
  final int y;

  Vector2(this.x, this.y);

  Vector2 rotate(Rotation rotation) => switch (rotation) {
    Rotation.left => Vector2(-y, x),
    Rotation.right => Vector2(y, -x),
    _ => throw ArgumentError.value(rotation, "rotation", "Must be a valid value of Rotation enum.")
  };

  Vector2 operator +(Vector2 other) {
    return Vector2(x + other.x, y + other.y);
  }

  Vector2 operator *(int scalar) {
    return Vector2(scalar * x, scalar * y);
  }
}

void main() {
  final inputContent = File('input.txt').readAsStringSync();
  var direction = Vector2(0, 1);
  var position = Vector2(0, 0);

  for (final (rotation, blocks) in inputContent.split(', ').map(parse)) {
    direction = direction.rotate(rotation);
    position += direction * blocks;
  }

  final distanceInBlocks = position.x.abs() + position.y.abs();
  print(distanceInBlocks);
}
