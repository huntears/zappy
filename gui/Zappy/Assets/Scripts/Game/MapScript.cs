using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Text.RegularExpressions;

public class MapScript : MonoBehaviour
{
    public GameObject chunksPrefab;
    public GameObject foodPrefab;
    public GameObject linematePrefab;
    public GameObject deraumerePrefab;
    public GameObject siburPrefab;
    public GameObject mendianePrefab;
    public GameObject phirasPrefab;
    public GameObject thystamePrefab;
    public GameObject playerPrefab;
    public GameObject eggPrefab;

    public int mapWitdh = 0, mapHeight = 0;
    public bool mapLoaded = false;
    public GameObject[,] chunks;
    public Dictionary<int, GameObject> players;
    public Dictionary<int, GameObject> eggs;

    public static MapScript mapScript;

    // Start is called before the first frame update
    void Start()
    {
        mapScript = this;
        if (!NetworkManager.isConnected)
            NetworkManager.StartClient("127.0.0.1", 4242);
        players = new Dictionary<int, GameObject>();
        eggs = new Dictionary<int, GameObject>();
    }

    public void CreateMap(int _mapWitdh, int _mapHeight)
    {
        mapLoaded = true;
        mapWitdh = _mapWitdh;
        mapHeight = _mapHeight;
        chunks = new GameObject[_mapHeight, _mapWitdh];
        for (int y = 0; y < _mapHeight; y++)
        {
            for (int x = 0; x < _mapWitdh; x++)
            {
                chunks[y, x] = Instantiate(
                    chunksPrefab,
                    new Vector3(
                        x * 10,
                        0,
                        y * 10),
                    Quaternion.identity
                ) as GameObject;
                chunks[y, x].transform.parent = this.transform;
            }
        }
    }

    public List<GameObject> GetChunkResources(GameObject _chunk, GameObject _resourcePrefab)
    {
        List<GameObject> resources = new List<GameObject>();

        foreach (Transform child in _chunk.transform)
        {
            if (child.gameObject.name == string.Format("{0}(Clone)", _resourcePrefab.name))
            {
                resources.Add(child.gameObject);
            }
        }
        return resources;
    }

    public void SpawnChunkResource(GameObject _chunk, GameObject _resourcePrefab)
    {
        Vector3 randomPos = new Vector3(Random.Range(-4, 4), 0, Random.Range(-4, 4));
        GameObject resource = Instantiate(
            _resourcePrefab,
            _chunk.transform.position + randomPos,
            Quaternion.identity
        ) as GameObject;
        resource.transform.parent = _chunk.transform;
        if (_resourcePrefab != foodPrefab)
        {
            resource.transform.localScale = new Vector3(0.5f, 0.5f, 0.5f);
        }
        else
        {
            resource.transform.position += new Vector3(0, 0.5f, 0);
        }
    }

    public void UpdateChunkResources(GameObject _chunk, GameObject _resourcePrefab, int _nbResources)
    {
        // error handling
        if (_nbResources < 0)
            return;

        List<GameObject> resources = GetChunkResources(_chunk, _resourcePrefab);
        if (resources.Count < _nbResources)
        {
            for (int count = resources.Count; count < _nbResources; count++)
            {
                SpawnChunkResource(_chunk, _resourcePrefab);
            }
        }
        else if (resources.Count > _nbResources)
        {
            for (int count = resources.Count - 1; count >= _nbResources; count--)
            {
                Destroy(resources[0]);
                resources.RemoveAt(0);
            }
        }
    }

    public void UpdateChunkResources(GameObject _chunk, int _nbFood, int _nbLinemate, int _nbDeraumere, int _nbSibur, int _nbMendiane, int _nbPhiras, int _nbThystame)
    {
        UpdateChunkResources(_chunk, foodPrefab, _nbFood);
        UpdateChunkResources(_chunk, linematePrefab, _nbLinemate);
        UpdateChunkResources(_chunk, deraumerePrefab, _nbDeraumere);
        UpdateChunkResources(_chunk, siburPrefab, _nbSibur);
        UpdateChunkResources(_chunk, mendianePrefab, _nbMendiane);
        UpdateChunkResources(_chunk, phirasPrefab, _nbPhiras);
        UpdateChunkResources(_chunk, thystamePrefab, _nbThystame);
    }

    public void UpdateChunkResources(int _x, int _y, int _nbFood, int _nbLinemate, int _nbDeraumere, int _nbSibur, int _nbMendiane, int _nbPhiras, int _nbThystame)
    {
        if (!mapLoaded)
            return;

        // error handling
        if (_x < 0 || _x >= mapWitdh)
            return;
        if (_y < 0 || _y > mapHeight)
            return;

        UpdateChunkResources(chunks[_y, _x], _nbFood, _nbLinemate, _nbDeraumere, _nbSibur, _nbMendiane, _nbPhiras, _nbThystame);
    }

    public void MovePlayer(int id, int x, int y, int dir)
    {
        // error handling
        if (x < 0 || x >= mapWitdh)
            return;
        if (y < 0 || y > mapHeight)
            return;

        Vector3 randomPos = new Vector3(Random.Range(-2, 2), 0, Random.Range(-2, 2));
        if (!players.ContainsKey(id))
        {
            // init new player
            players[id] = Instantiate(
                playerPrefab,
                chunks[y, x].transform.position + randomPos,
                Quaternion.identity
            ) as GameObject;
            players[id].transform.localScale = new Vector3(0.5f, 0.5f, 0.5f);
        }
        players[id].transform.position = chunks[y, x].transform.position + randomPos;
        players[id].transform.position += new Vector3(0, 1.4f, 0);
        if (dir == 1)
        {
            players[id].transform.rotation = Quaternion.Euler(new Vector3(0, 180, 0));
        }
        else if (dir == 2)
        {
            players[id].transform.rotation = Quaternion.Euler(new Vector3(0, 90, 0));
        }
        else if (dir == 3)
        {
            players[id].transform.rotation = Quaternion.Euler(new Vector3(0, 0, 0));
        }
        else if (dir == 4)
        {
            players[id].transform.rotation = Quaternion.Euler(new Vector3(0, -90, 0));
        }
    }

    public void RemovePlayer(int id)
    {
        if (!players.ContainsKey(id))
            return;
        Destroy(players[id]);
        players.Remove(id);
    }

    public void AddEgg(int id, int x, int y)
    {
        // error handling
        if (x < 0 || x >= mapWitdh)
            return;
        if (y < 0 || y > mapHeight)
            return;

        Vector3 randomPos = new Vector3(Random.Range(-4, 4), 0, Random.Range(-4, 4));
        if (!eggs.ContainsKey(id))
        {
            // init new player
            eggs[id] = Instantiate(
                eggPrefab,
                chunks[y, x].transform.position + randomPos,
                Quaternion.identity
            ) as GameObject;
            eggs[id].transform.localScale = new Vector3(0.13f, 0.13f, 0.13f);
        }
    }

    public void RemoveEgg(int id)
    {

        if (!eggs.ContainsKey(id))
            return;
        Destroy(eggs[id]);
        eggs.Remove(id);
    }

    public bool ParseCommand(string command)
    {
        try
        {
            if (command == "" || command == "WELCOME")
                return false;
            if (command.StartsWith("msz "))
            {
                var regex = new Regex(@"msz (\d+) (\d+)");
                var match = regex.Match(command);
                if (match.Success)
                {
                    CreateMap(
                        int.Parse(match.Groups[1].Value),
                        int.Parse(match.Groups[2].Value)
                        );
                    return true;
                }
            }
            else if (command.StartsWith("bct "))
            {
                var regex = new Regex(@"bct (\d+) (\d+) (\d+) (\d+) (\d+) (\d+) (\d+) (\d+) (\d+)");
                var match = regex.Match(command);
                if (match.Success)
                {
                    UpdateChunkResources(
                        int.Parse(match.Groups[1].Value),
                        int.Parse(match.Groups[2].Value),
                        int.Parse(match.Groups[3].Value),
                        int.Parse(match.Groups[4].Value),
                        int.Parse(match.Groups[5].Value),
                        int.Parse(match.Groups[6].Value),
                        int.Parse(match.Groups[7].Value),
                        int.Parse(match.Groups[8].Value),
                        int.Parse(match.Groups[9].Value));
                    return true;
                }
            }
            else if (command.StartsWith("pnw "))
            {
                var regex = new Regex(@"pnw (\d+) (\d+) (\d+) ([1-4]) (\d+) (.*)");
                var match = regex.Match(command);
                if (match.Success)
                {
                    MovePlayer(
                        int.Parse(match.Groups[1].Value),
                        int.Parse(match.Groups[2].Value),
                        int.Parse(match.Groups[3].Value),
                        int.Parse(match.Groups[4].Value)
                        );
                    return true;
                }
            }
            else if (command.StartsWith("ppo "))
            {
                var regex = new Regex(@"ppo (\d+) (\d+) (\d+) ([1-4])");
                var match = regex.Match(command);
                if (match.Success)
                {
                    MovePlayer(
                        int.Parse(match.Groups[1].Value),
                        int.Parse(match.Groups[2].Value),
                        int.Parse(match.Groups[3].Value),
                        int.Parse(match.Groups[4].Value)
                        );
                    return true;
                }
            }
            else if (command.StartsWith("pdi "))
            {
                var regex = new Regex(@"pdi (\d+)");
                var match = regex.Match(command);
                if (match.Success)
                {
                    RemovePlayer(
                        int.Parse(match.Groups[1].Value)
                        );
                    return true;
                }
            }
            else if (command.StartsWith("enw "))
            {
                var regex = new Regex(@"enw (\d+) (\d+) (\d+) (\d+)");
                var match = regex.Match(command);
                if (match.Success)
                {
                    AddEgg(
                        int.Parse(match.Groups[1].Value),
                        int.Parse(match.Groups[3].Value),
                        int.Parse(match.Groups[4].Value)
                        );
                    return true;
                }
            }
            else if (command.StartsWith("ebo ") || command.StartsWith("edi "))
            {
                var regex = new Regex(@"(enw|edi) (\d+)");
                var match = regex.Match(command);
                if (match.Success)
                {
                    RemoveEgg(
                        int.Parse(match.Groups[2].Value)
                        );
                    return true;
                }
            }
            else
            {
                Debug.Log("Command not found: " + command);
            }
        }
        catch { }
        return false;
    }

    static bool firstFrame = true;
    // Update is called once per frame
    void Update()
    {
        if (firstFrame)
        {
            firstFrame = false;
            return;
        }
        if (!NetworkManager.isConnected)
            return;
        try
        {
            while (NetworkManager.socketStream.DataAvailable)
            {
                string cmd = NetworkManager.readSocket();
                ParseCommand(cmd);
            }
        }
        catch { }
    }
}
