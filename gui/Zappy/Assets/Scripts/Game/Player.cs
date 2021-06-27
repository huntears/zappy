using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{
    public Vector3 actual = Vector3.forward;

    private bool isIncantate = false;
    private bool isFork = false;

    // Inventory
    int nbFood = 0;
    int nbLinemate = 0;
    int nbDeraumer = 0;
    int nbSibur = 0;
    int nbMendianephiras = 0;
    int nbThystame = 0;

    string message = "";


    public Player(int _id, int _x, int _y, int _direction) {

    }

    public void Start()
    {

    }

    public void Update()
    {

    }

    // public void GoForward()
    // {
    //     GetComponent<Rigidbody>().AddForce(actual);
    // }

    // public void TurnRight()
    // {
    //     if (actual == Vector3.forward)
    //         actual = Vector3.right;
    //     if (actual == Vector3.right)
    //         actual = Vector3.back;
    //     if (actual == Vector3.back)
    //         actual = Vector3.left;
    //     if (actual == Vector3.left)
    //         actual = Vector3.forward;
    // }

    // public void TurnLeft()
    // {
    //     if (actual == Vector3.forward)
    //         actual = Vector3.left;
    //     if (actual == Vector3.right)
    //         actual = Vector3.forward;
    //     if (actual == Vector3.back)
    //         actual = Vector3.right;
    //     if (actual == Vector3.left)
    //         actual = Vector3.back;
    // }

    public void SetPos(int _x, int _y, int _direction)
    {
    }

    public void StartIncantation()
    {
        isIncantate = true;
    }

    public void EndIncantation(bool _success)
    {
        isIncantate = false;
    }

    public void StartFork()
    {
        isFork = true;
    }

    public void EndFork()
    {
        isFork = false;
    }

    public void Eject()
    {
    }

    public void IsEjected()
    {
    }

    public void TakeResource(int _resourceType)
    {
    }

    public void SetResource(int _resourceType)
    {
    }

    public void SetInventory(int _nbFood, int _nbLinemate, int _nbDeraumere, int _nbSibur, int _nbMendianephiras, int _nbThystame)
    {
        nbFood = _nbFood;
        nbLinemate = _nbLinemate;
        nbDeraumer = _nbDeraumere;
        nbSibur = _nbSibur;
        nbMendianephiras = _nbMendianephiras;
        nbThystame = _nbThystame;
    }

    public void BroadcastMessage(string _message)
    {
        message = _message;
    }

    public void Die()
    {

    }
}