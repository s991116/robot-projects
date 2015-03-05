#ifndef DETECTTEMPLATEOBJECT_H
#define	DETECTTEMPLATEOBJECT_H

#include <Position.h>
#include <DetectObject.h>

class DetectTemplateObject : public DetectObject {
public:
    DetectTemplateObject(cv::Mat imageTemplate);    
    void GetPosition(cv::Mat image, Position* position, std::vector< cv::Point2f >* scene_corners);
    
    private:
	cv::Mat _template;
	int _match_method;
};

#endif	/* DETECTTEMPLATEOBJECT_H */