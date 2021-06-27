using System.Collections;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System;
using System.Text;
using System.IO;
using System.Threading;
using UnityEngine.SceneManagement;
using UnityEngine;

public class NetworkManager : MonoBehaviour
{
    private static TcpClient socket;
    public static NetworkStream socketStream;
    public static StreamWriter socketStreamWriter;
    public static StreamReader socketStreamReader;
    public static bool isConnected = false;

    void Start()
    {
        DontDestroyOnLoad(this.gameObject);
    }

    private void OnDestroy()
    {
        if (isConnected)
        {
            socketStreamWriter.Close();
            socketStreamReader.Close();
            socketStream.Close();
            socket.Close();
            isConnected = false;
        }
    }

    public static void StartClient(string host, int port)
    {
        try
        {
            socket = new TcpClient(host, port);
            if (socket == null || !socket.Connected)
            {
                ErrorText.TextChange("Connection error");
                return;
            }
            socketStream = socket.GetStream();
            socketStreamWriter = new StreamWriter(socketStream);
            socketStreamReader = new StreamReader(socketStream);
            socketStreamWriter.WriteLine("GRAPHIC");
            socketStreamWriter.Flush();
            isConnected = true;
            SceneManager.LoadScene("Game");
        }
        catch (Exception e)
        {
            ErrorText.TextChange(e.ToString());
        }
    }

    public static string readSocket()
    {
        if (!isConnected)
            throw new IOException();
        if (!socketStream.DataAvailable)
            throw new IOException();
        return socketStreamReader.ReadLine();
    }
}