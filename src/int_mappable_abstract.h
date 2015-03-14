#ifndef INT_MAPPABLE_H
#define INT_MAPPABLE_H

class IntMappable
{
	public:
		virtual unsigned int getPixelIntensity(unsigned int row, unsigned int col) = 0;
		virtual unsigned int getHeight() = 0;
		virtual unsigned int getWidth() = 0;
		virtual ~IntMappable() = 0;
	private:
		
};

inline IntMappable::~IntMappable() {};

#endif
