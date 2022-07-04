//
// 图
// Created by mason on 2022/7/4.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_VEX 8			 /* 最大顶点数，应由用户定义 */
#define GRAPH_INFINITY 65535 /* 用65535来代表∞ */

typedef int VertexType;
typedef int EdgeType;
typedef struct {
	VertexType vexs[MAX_VEX];
	EdgeType arc[MAX_VEX][MAX_VEX];
	int numNodes, numEdges;
} MatrixGraph;

void create_matrix_graph(MatrixGraph *graph) {
	printf("input node and edge:\n");
	scanf("%d,%d", &graph->numNodes, &graph->numEdges);
	for (int i = 0; i < graph->numNodes; i++) {
		scanf("%d", &graph->vexs[i]);
	}
	for (int i = 0; i < graph->numNodes; i++) {
		for (int j = 0; j < graph->numNodes; j++) {
			graph->arc[i][j] = GRAPH_INFINITY;
		}
	}

	int x;
	int y;
	int w;
	for (int k = 0; k < graph->numEdges; k++) {
		printf("输入边(vi,vj)上的下标i，下标j和权w:\n");
		scanf("%d,%d,%d", &x, &y, &w);
		graph->arc[x][y] = w;
		graph->arc[y][x] = graph->arc[x][y];
	}
}

int main(void) {
	MatrixGraph graph;
	create_matrix_graph(&graph);
	return EXIT_SUCCESS;
}
