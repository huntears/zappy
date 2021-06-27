using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ErrorText : MonoBehaviour
{
    void Start()
    {
    }

    void Update()
    {
    }

    public static void TextChange(string error)
    {
        Text changingText = GameObject.Find("ErrorText").GetComponent<Text>();
        changingText.text = error;
    }
}
