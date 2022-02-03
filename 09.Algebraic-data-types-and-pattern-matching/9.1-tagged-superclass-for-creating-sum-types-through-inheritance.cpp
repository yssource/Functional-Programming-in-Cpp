class state_t {
// It shouldn't be possible to create instances of this
// class, so make the constructor protected. It can
// be called only by classes that inherit from state_t.
protected:
// Each subclass should pass a different
// value for the type argument. You can
// use it as an efficient replacement for
// dynamic_cast.
  state_t(int type)
    : type(type) {}

public:
  virtual ~state_t() {}
  int type;
};