#pragma once
#include "raylib.h"
#include "Node.h"
#include <vector>

class Pathfind
{
public:

#define ROWS 10
#define COLS 20
#define NODE_SIZE 50

    static const int screenWidth = 1000;
    static const int screenHeight = 500;

    std::vector<std::vector<Node>> grid;

    Node* pointA = nullptr;
    Node* pointB = nullptr;
    Node* current = nullptr;

    bool startSearch = false;
    bool searchFinished = false;

    std::vector<Node*> stack;
    std::vector<Node*> finalPath;

    int drawIndex = 0;
    float drawTimer = 0;
    float drawSpeed = 0.05f;

    void Main();
    void Start();
    void Update();
    void Interaction();
    void Draw();

    Node* GetRandomNode();
    void Restart();

    std::vector<Node*> GetNeighbors(Node* n);
    void StepRandomBacktracking();
    void BuildFinalPath(Node* end);
};