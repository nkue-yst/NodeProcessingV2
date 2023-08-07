/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/08
 * Edited:  2023/08/07
 **********/

#pragma once

#include <string>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#endif

#include "GL/gl.h"
#include "opencv2/opencv.hpp"

#include "NodeContent.h"
#include "NodeStyle.h"
#include "Pin.h"

class Node
{
public:
    Node(NodeType type = NodeType_UNDEFINED);
    virtual ~Node();

    ///////////////////////////////////
    ///// Get content by template /////
    ///////////////////////////////////
    NodeContent* m_content;

    template<typename T>
    T getContent(Pin::Type pin_type);

    template<> cv::Mat getContent(Pin::Type pin_type)
    {
        if (pin_type == Pin::Type::RGB)
        {
            return this->m_content->m_image;
        }
    }

    template<> int32_t getContent(Pin::Type pin_type)
    {
        if (pin_type == Pin::Type::VALUE)
        {
            return this->m_content->m_value;
        }
    }

    // cv::MatからGLuintへの変換
    static GLuint convert_func(cv::Mat* mat)
    {
        if (mat->empty())
        {
            return 0;
        }

        GLuint texture_id;

        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

        cv::cvtColor((*mat), (*mat), cv::COLOR_RGB2BGR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (*mat).cols, (*mat).rows, 0, GL_RGB, GL_UNSIGNED_BYTE, (*mat).ptr());

        return texture_id;
    };

    void draw();

    void setDirtyFlag(int32_t new_priority = -1);

protected:
    virtual void drawInPins();
    virtual void drawOutPins();

    virtual void drawContent() = 0;

public:
    uint32_t m_id;
    std::string m_name;

    std::vector<class Pin*> m_in_pins;
    std::vector<class Pin*> m_out_pins;

    int32_t m_priority;

    bool m_need_update;

protected:
    uint32_t m_node_width  = 100;
    uint32_t m_node_height = 100;

    NodeType m_type;
};
