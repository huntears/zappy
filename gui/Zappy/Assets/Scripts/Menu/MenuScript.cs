using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MenuScript : MonoBehaviour
{
    private string host;
    private int port;

    public void IpChange(string _host)
    {
        host = _host;
    }

    public void PortChange(string _port)
    {
        try
        {
            port = int.Parse(_port);
        }
        catch
        {
            port = -1;
        }
    }

    public void PlayButtonClick()
    {
        NetworkManager.StartClient(host, port);
    }

    public void QuitButtonClick()
    {
        Application.Quit();
    }
}