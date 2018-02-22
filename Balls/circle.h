

class Circle
{
public:
	Circle(double x, double y, double dx, double dy, int r, std::vector<int> color);
	int getX();
	int getY();
	double getDx();
	double getDy();
	std::vector<int> getColor();
	int getRadius();
	void changeColor();
	void move(int screen_x, int screen_y);
	double getnextx();
	double getnexty();
	void setdx(double dx);
	void setdy(double dy);
	void gravity(int screen_x, int screen_y);
	void checkForCollision(int n, std::vector<Circle> &circles);
	bool willCollide(int n, int i, std::vector<Circle> &circles);
	void collide(int p1, int p2, std::vector<Circle> &particles);

protected:
	int mRadius;
	double mX, mY, mDx, mDy;
	std::vector<int> mColor;
};




