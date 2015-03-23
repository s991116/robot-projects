#ifndef DETECTTEMPLATEOBJECT_H
#define	DETECTTEMPLATEOBJECT_H

#include <Position.h>
#include <DetectObject.h>

class DetectTemplateObject : public DetectObject {
public:
    DetectTemplateObject(cv::Mat imageTemplate);
	void GetPosition(cv::Mat image, ObjectPosition* position);
    
    private:
	cv::Mat _template;
	int _match_method;
};

#endif	/* DETECTTEMPLATEOBJECT_H */