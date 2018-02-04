// **************************************************************
// *		   
// *  quadtree.h
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

#include <math.h>

class Quadtree
{
	public:
	
	Quadtree();

	Quadtree(PNG const & source, int resolution);

	Quadtree(Quadtree const & other);

	~Quadtree();

	Quadtree const & operator= (Quadtree const & other);

	void buildTree(PNG const & source, int resolution);

	RGBAPixel getPixel(int x, int y) const ;

	PNG decompress() const;

	int pruneSize(int tolerance) const;
	
	void clockwiseRotate();

	void prune (int tolerance);

	int idealPrune (int numLeaves) const;

	private:

	// A simple class representing a single node of a Quadtree.
	// You may want to add to this class; in particular, it could probably
	// use a constructor or two...
	class QuadtreeNode
	{
		public:
		QuadtreeNode* nwChild;  // pointer to northwest child
		QuadtreeNode* neChild;  // pointer to northeast child
		QuadtreeNode* swChild;  // pointer to southwest child
		QuadtreeNode* seChild;  // pointer to southeast child

		RGBAPixel element;  // the pixel stored as this node's "data"
	
		QuadtreeNode (RGBAPixel color);
		QuadtreeNode();

	};

	int length;

	QuadtreeNode* root;    // pointer to root of quadtree
	
	QuadtreeNode* _copy(QuadtreeNode * const & curr);

	QuadtreeNode* _build(PNG const & source, int x, int y, int resolution);

	void _clear(QuadtreeNode * & curr);
	
	QuadtreeNode* _getNode(QuadtreeNode* curr, int x, int y, int startx, int starty, int len) const;
	
	void _rotate(QuadtreeNode * & curr);

	void _pruning(QuadtreeNode * & curr, int tolerance);

	bool _prunable(QuadtreeNode * curr, RGBAPixel avg, int tolerance) const;

	int _size(QuadtreeNode * curr, int tolerance) const;

	/**** Functions added for testing/grading                ****/
	/**** Do not remove this line or copy its contents here! ****/
	#include "quadtree_given.h"
};

#endif
