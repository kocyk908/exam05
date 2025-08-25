#ifndef VECT2
# define VEC2

# include <iostream>

class vect2
{
	private:
		int _x;
		int _y;
	public:
		vect2() : _x(0), _y(0)
		{

		}

		vect2(int x, int y) : _x(x), _y(y)
		{

		}

		vect2(const vect2 &src)
		{
			*this = src;
		}

		~vect2()
		{

		}

		vect2& operator=(const vect2 &src)
		{
			this->_x = src._x;
			this->_y = src._y;
			return(*this);
		}
		
		int operator[](int index) const
		{
			if (index == 0)
				return (this->_x);
			return (this->_y);
		}

		int& operator[](int index)
		{
			if (index == 0)
				return (this->_x);
			return (this->_y);
		}

		vect2& operator++()
		{
			this->_x += 1;
			this->_y += 1;
			return (*this);
		}

		vect2 operator++(int)
		{
			vect2 temp = *this;

			++(*this);
			return (temp);
		}

		vect2& operator--()
		{
			this->_x -= 1;
			this->_y -= 1;
			return (*this);
		}

		vect2 operator--(int)
		{
			vect2 temp = *this;

			--(*this);
			return (temp);
		}

		vect2& operator+=(const vect2 &src)
		{
			this->_x += src._x;
			this->_y += src._y;
			return(*this);
		}

		vect2& operator-=(const vect2 &src)
		{
			this->_x -= src._x;
			this->_y -= src._y;
			return(*this);
		}

		vect2& operator-()
		{
			this->_x *= -1;
			this->_y *= -1;
			return(*this);
		}

		vect2 operator*=(int num)
		{
			this->_x *= num;
			this->_y *= num;
			return (*this);
		}

		vect2 operator+(const vect2 &src) const
		{
			vect2 temp = *this;

			temp._x += src._x;
			temp._y += src._y;
			return (temp);
		}

		vect2 operator-(const vect2 &src) const
		{
			vect2 temp = *this;

			temp._x -= src._x;
			temp._y -= src._y;
			return (temp);
		}

		vect2 operator*(int num) const
		{
			vect2 temp = *this;

			temp._x *= num;
			temp._y *= num;
			return (temp);
		}

		bool operator==(const vect2 &src)
		{
			if (this->_x == src._x && this->_y == src._y)
				return (true);
			return (false);
		}

		bool operator!=(const vect2 &src)
		{
			if (this->_x != src._x && this->_y != src._y)
				return (true);
			return (false);
		}

};

vect2 operator*(int num, const vect2 &src)
{
	return (src * num);
}

std::ostream &operator<<(std::ostream &os, const vect2 &src)
{
	std::cout << "{" << src[0] << ", " << src[1] << "}";
	return (os);
}

#endif