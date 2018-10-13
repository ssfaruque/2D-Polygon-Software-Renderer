#ifndef CLI_H
#define CLI_H

#include <vector>
#include <string>
#include "types.h"

class Scene;

class Cli
{
    private:
        Scene* m_scene;

    private:
        void cmdLoad(const std::string fileName);
        void cmdSave(const std::string fileName);
        void cmdSetLineDrawingMode(int id, int drawWithBresenham);
        void cmdSetClippingWindow(float xmin, float xmax, float ymin, float ymax);
        void cmdRasterize(int id, const Color color);
        void cmdDDA(float x1, float y1, float x2, float y2);
        void cmdBresenham(float x1, float y1, float x2, float y2);
        void cmdPolygon(const std::vector<Vertex>& vertices);
        void cmdTranslate(int id, float xTrans, float yTrans);
        void cmdScale(int id, float xScale, float yScale);
        void cmdRotate(int id, float angle);

        std::vector<std::string> getTokensFromLine(const std::string& line) const;

    public:
        Cli(Scene* scene);
        ~Cli() = default;

        void run();
        void processInput();
};



#endif  // CLI_H