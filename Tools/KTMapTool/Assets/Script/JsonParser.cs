using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class JsonParser : MonoBehaviour 
{
	public void LoadFrom(string jsonFileName)
	{
		Debug.Log ("LoadFrom: " + Application.dataPath + ", " + jsonFileName);

	}
}
