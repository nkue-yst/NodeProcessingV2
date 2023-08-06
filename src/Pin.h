/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/09
 * Edited:  2023/08/06
 **********/

#ifndef __PIN_H__
#define __PIN_H__

#include <cstdint>
#include <string>
#include <vector>

#include "imgui.h"

#include "Node.h"

class Pin
{
public:
    enum Type
    {
        RGB,         // カラー情報
        VALUE,       // 数値
    
        UNDEFINED    // 未定義
    };

    Pin(class Node* owner, int32_t id, Type type, std::string name);
    ~Pin();

    bool operator==(const Type rhs) const
    {
        return this->m_type == rhs;
    }

    bool operator!=(const Type rhs) const
    {
        return this->m_type != rhs;
    }

    void drawAsInput();
    void drawAsOutput();

    int getShape();

    int32_t m_id;
    std::string m_name;
    Type m_type;

    std::vector<class Pin*> m_connected_pins;

    class Node* m_owner;
};

#endif
