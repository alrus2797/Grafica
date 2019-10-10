#ifndef LINE2D_H
#define LINE2D_H

#include "Point2d.h"

bool is_x_minor(Point2d p1, Point2d p2){
	return p1.x < p2.x;
}

bool is_y_minor(Point2d p1, Point2d p2){
	return p1.y < p2.y;
}

constexpr double pi = 3.14159265358979323846;

struct Line2d{
	Point2d source;
	Point2d destination;

	Line2d(){

	}

	Line2d(Point2d p1, Point2d p2){
		this->source = p1;
		this->destination = p2;
	}

	Line2d(int x1, int y1, int x2, int y2){
		this->source = Point2d(x1, y1);
		this->destination = Point2d(x2, y2);
	}

	void operator = (Line2d const & other){
		this->source = other.source;
		this->destination = other.destination;
	}

	//Here goes the defailt draw (basic draw or incremental draw)
	void draw(){
		inc_draw();
	}

	void basic_draw(){
		Point2d p1, p2;
		p1 = this->source;
		p2 = this->destination;
	    int x, y;
		float a;
		
		int value;

		a = (p2.y-p1.y) / (p2.x - p1.x);
		printf("%i %i\n", p1.x, p2.x);
		for (size_t x = p1.x; x <= p2.x; x++)
		{
			y = (p1.y + a * (x - p1.x));
			//printf("%i %i\n", x, y);
			draw_point(x,y);
		}
	}

	void inc_draw(){

		Point2d p1, p2;
		p1 = this->source;
		p2 = this->destination;
		int dx, dy, e_inc, ne_inc, d, x, y;

		if (p1.x == p2.x){
			// printf("jeje\n");
			int y1, y2;
			y1 = ( is_y_minor(p1, p2) ) ? p1.y : p2.y;
			y2 = ( is_y_minor(p1, p2) ) ? p2.y : p1.y;
			x = p1.x;
			while(y1 < y2){
				draw_point(x, y1);
				y1++;
			}
			return;
		}

		if (!is_x_minor(p1,p2)){
			int t_x = p1.x, t_y = p1.y;
			p1.x = p2.x; p1.y = p2.y;
			p2.x = t_x; p2.y = t_y;
		}
		dx = p2.x - p1.x;
		dy = abs(p2.y - p1.y);

		d = 2 * dy - dx;

		e_inc = 2 * dy;
		ne_inc = 2 * (dy - dx);
		

		x = p1.x;
		y = p1.y;

		draw_point(x, y);

		while(x < p2.x){
			if (d <= 0){
				d = d + e_inc;
				x++;
			}
			else{
				d = d + ne_inc;
				x++;
				if (is_y_minor(p1,p2))
					y++;
				else
					y--;
			}
			//printf("%i %i d: %i\n", x, y, d);
			draw_point(x,y);
		}
	}

	void move(int x, int y){
		this->source.x += x;
		this->source.y += y;

		this->destination.x += x;
		this->destination.y += y;
	}

	void scalate(float x, float y){
		float scale = 1;
		// printf("%f, %f, %f\n", x, y, scale);
		this->source.x *= scale * x;
		this->source.y *= scale * y;

		this->destination.x *= scale * x;
		this->destination.y *= scale * y;
	}

	void rotate(float angle){
		float radians = angle * pi / 180;
		// radians = angle;
		//printf("Angle radians: %f: \n", radians);
		float x_temp = this->source.x;
		this->source.x = this->source.x * cos(radians) - this->source.y * sin(radians);
		this->source.y = x_temp * sin(radians) + this->source.y * cos(radians);
		x_temp = this->destination.x;
		this->destination.x = this->destination.x * cos(radians) - this->destination.y * sin(radians);
		this->destination.y = x_temp * sin(radians) + this->destination.y * cos(radians);

		// std::cout<< "Point: " << this->source << " - "<< this->destination << std::endl;
	}

};

#endif