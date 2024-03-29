/**********
 * Author:  Y.Nakaue
 * Created: 2023/07/29
 * Edited:  2023/08/08
 **********/

#ifndef __BINARIZATION_NODE_H__
#define __BINARIZATION_NODE_H__

#include "GraphicsProcessingNode.h"

class BinarizationNode : public GraphicsProcessingNode
{
public:
    BinarizationNode();

protected:
    void drawContent() override;
    void process() override;

private:
    double m_threshold;
};

#endif
