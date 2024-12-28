#include <iostream>
#include <limits>
#include <queue>
#include <vector>

class Graph
{
  public:
  int n;
  std::vector<std::vector<std::pair<int, ssize_t> > > ls;

  Graph (int n) : n (n), ls (n) {}

  void
  add_edge (int u, int v, ssize_t w)
  {
    ls[u].emplace_back( v, w );
  }

  ssize_t
  dijkstra (int start, int end)
  {
    const ssize_t INF = std::numeric_limits<ssize_t>::max ();
    std::vector<ssize_t> dist (n, INF);
    dist[start] = 0;

    using Pli = std::pair<ssize_t, int>;
    std::priority_queue<Pli, std::vector<Pli>, std::greater<> > pq;
    pq.emplace( 0, start );

    while (!pq.empty ())
      {
        auto [cur, u] = pq.top ();
        pq.pop ();

        if (cur > dist[u])
          continue;

        if (u == end)
          return dist[end];

        for (auto &edge : ls[u])
          {
            int v = edge.first;
            ssize_t w = edge.second;
            ssize_t newDist = dist[u] + w;
            if (newDist < dist[v])
              {
                dist[v] = newDist;
                pq.push ({ newDist, v });
              }
          }
      }

    return INF;
  }
};

int
main ()
{
  ssize_t a, b;
  int M, x, y;
  std::cin >> a >> b >> M >> x >> y;

  Graph g (M);

  for (int z = 0; z < M; ++z)
    {
      int next1 = (z + 1) % M;
      g.add_edge (z, next1, a);

      ssize_t zSq = (ssize_t) z * z;
      int next2 = (zSq + 1) % M;
      g.add_edge (z, next2, b);
    }

  if (x == y)
    {
      std::cout << 0 << "\n";
      return 0;
    }

  ssize_t ans = g.dijkstra (x, y);

  if (ans == std::numeric_limits<ssize_t>::max ())
      std::cout << 0 << "\n";

  else
      std::cout << ans << "\n";

  return 0;
}
