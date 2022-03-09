#ifndef VIEWER_H
#define VIEWER_H

class Viewer {
  public:
    Viewer(const char* filename, int width, int height) : _filename{filename}, _width{width}, _height{height} {}
    void run();

  private:
    const char* _filename;
    int _width;
    int _height;
};

#endif