#include "Pathfind.h"
#include <algorithm>

void Pathfind::Main()
{
}

void Pathfind::Start()
{
    grid.clear();
    finalPath.clear();
    stack.clear();
    startSearch = false;
    searchFinished = false;

    for (int row = 0; row < ROWS; row++)
    {
        float y = NODE_SIZE * row;
        std::vector<Node> rowNodes;
        for (int col = 0; col < COLS; col++)
        {
            float x = NODE_SIZE * col;
            rowNodes.emplace_back(row, col, Vector2{ x, y }, Vector2{ NODE_SIZE, NODE_SIZE });
        }
        grid.push_back(rowNodes);
    }

    for (int i = 0; i < (int)(ROWS * COLS * 0.1f); i++)
        GetRandomNode()->blocked = true;

    pointA = GetRandomNode();
    pointA->blocked = false;
    pointA->fillColor = SKYBLUE;
    pointA->text = "A";

    pointB = GetRandomNode();
    pointB->blocked = false;
    pointB->fillColor = GREEN;
    pointB->text = "B";

    current = pointA;
    stack.push_back(pointA);
}

void Pathfind::Update()
{
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            Node& n = grid[r][c];

            if (&n == pointA)
            {
                n.fillColor = SKYBLUE;
                n.text = "A";
                continue;
            }
            if (&n == pointB)
            {
                n.fillColor = GREEN;
                n.text = "B";
                continue;
            }

            if (n.blocked)
                n.fillColor = DARKGRAY;
            else if (n.visited)
                n.fillColor = RED;
            else
                n.fillColor = GRAY;

            n.text = "";
        }
    }

    if (searchFinished)
    {
        drawTimer += GetFrameTime();
        if (drawTimer >= drawSpeed && drawIndex < (int)finalPath.size())
        {
            drawTimer = 0;
            drawIndex++;
        }

        for (int i = 0; i < drawIndex; i++)
        {
            Node* n = finalPath[i];
            if (n != pointA && n != pointB)
                n->fillColor = YELLOW;
        }
    }

    if (startSearch && !searchFinished)
        StepRandomBacktracking();
}

void Pathfind::Interaction()
{
    if (IsKeyPressed(KEY_R))
        Restart();

    if (IsKeyPressed(KEY_ENTER))
    {
        startSearch = true;
        searchFinished = false;
        finalPath.clear();
        stack.clear();
        drawIndex = 0;
        drawTimer = 0;

        current = pointA;
        stack.push_back(pointA);
    }
}

void Pathfind::Draw()
{
    for (auto& row : grid)
        for (auto& n : row)
            n.Draw();
}

Node* Pathfind::GetRandomNode()
{
    while (true)
    {
        int r = GetRandomValue(0, ROWS - 1);
        int c = GetRandomValue(0, COLS - 1);
        if (!grid[r][c].blocked)
            return &grid[r][c];
    }
}

void Pathfind::Restart()
{
    Start();
}

std::vector<Node*> Pathfind::GetNeighbors(Node* n)
{
    std::vector<Node*> neighbors;
    int r = n->row;
    int c = n->col;

    if (r > 0) neighbors.push_back(&grid[r - 1][c]);
    if (r < ROWS - 1) neighbors.push_back(&grid[r + 1][c]);
    if (c > 0) neighbors.push_back(&grid[r][c - 1]);
    if (c < COLS - 1) neighbors.push_back(&grid[r][c + 1]);

    for (int i = neighbors.size() - 1; i > 0; i--)
    {
        int j = GetRandomValue(0, i);
        std::swap(neighbors[i], neighbors[j]);
    }

    return neighbors;
}

void Pathfind::StepRandomBacktracking()
{
    if (current == pointB)
    {
        BuildFinalPath(current);
        searchFinished = true;
        return;
    }

    current->visited = true;

    std::vector<Node*> neighbors = GetNeighbors(current);
    std::vector<Node*> valid;

    for (Node* n : neighbors)
        if (!n->blocked && !n->visited)
            valid.push_back(n);

    if (!valid.empty())
    {
        Node* next = valid[GetRandomValue(0, valid.size() - 1)];
        next->parent = current;
        stack.push_back(next);
        current = next;
    }
    else
    {
        stack.pop_back();
        if (stack.empty())
        {
            searchFinished = true;
            return;
        }
        current = stack.back();
    }
}

void Pathfind::BuildFinalPath(Node* end)
{
    finalPath.clear();
    Node* temp = end;
    while (temp)
    {
        finalPath.push_back(temp);
        temp = temp->parent;
    }
    std::reverse(finalPath.begin(), finalPath.end());
}