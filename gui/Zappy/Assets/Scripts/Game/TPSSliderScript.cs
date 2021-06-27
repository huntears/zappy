using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TPSSliderScript : MonoBehaviour
{
    private float lastValue = 0f;

    // Start is called before the first frame update
    void Start()
    {
    }

    double logslider(float position)
    {
        // from
        double minp = 0;
        double maxp = 100;

        // to
        double minv = Math.Log(1);
        double maxv = Math.Log(10000);

        double scale = (maxv - minv) / (maxp - minp);
        return Math.Exp(minv + scale * (position - minp));
    }

    void Update()
    {
        float currentValue = GameObject.Find("Slider").GetComponent<Slider>().value;

        if (currentValue != lastValue) {
            int tps = (int)logslider(currentValue);
            GameObject.Find("TPSText").GetComponent<Text>().text = tps.ToString();
            NetworkManager.socketStreamWriter.WriteLine("sst " + tps.ToString());
            NetworkManager.socketStreamWriter.Flush();
        }
        lastValue = currentValue;
    }
}