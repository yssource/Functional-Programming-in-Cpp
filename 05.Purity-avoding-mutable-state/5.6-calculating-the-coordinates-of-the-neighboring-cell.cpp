enum direction_t {
  Left,
  Right,
  Up,
  Down
};

class position_t {
public:
  position_t(position_t const& original, direction_t direction);

  int x;
  int y;
};

class maze_t {
public:
  auto is_wall(position_t) const -> bool;
};

auto next_position(direction_t direction, position_t const& previous_position, maze_t const& maze)
  -> position_t {
  position_t const desired_position{ previous_position, direction };
 
  return maze.is_wall(desired_position) ? previous_position
                                        : desired_position;   
}

position_t::position_t(position_t const& original, direction_t direction)
// Uses the ternary operator to match against the possible direction values
// and initialize the correct values of x and y. You could also use a switch
// statement in the body of the constructor.
  : x{ direction == Left  ? original.x - 1 :
       direction == Right ? original.x + 1 :
                            original.x     }
  , y{ direction == Up    ? original.y + 1 :
       direction == Down  ? original.y - 1 :
                            original.y     } {}
