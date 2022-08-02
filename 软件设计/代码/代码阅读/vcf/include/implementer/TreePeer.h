/* Generated by Together */


#ifndef TREEPEER_H
#define TREEPEER_H



namespace VCF{

class ImageList;

class TreeItem;

class TreeModel;


/** @interface */

class APPKIT_API TreePeer : public ControlPeer {
public:    
	virtual ~TreePeer(){};

    virtual TreeModel* getTreeModel() = 0;

	virtual void setTreeModel( TreeModel* model ) = 0;

    virtual double getItemIndent() = 0;

    virtual void setItemIndent( const double& indent ) = 0;

    virtual ImageList* getImageList() = 0;

    virtual void setImageList( ImageList* imageList ) = 0;

	virtual void clear() = 0;
	
	virtual void addItem( TreeItem* item ) = 0;
};

};

#endif //TREEPEER_H