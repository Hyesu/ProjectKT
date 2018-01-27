using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class MouseEventHandler : MonoBehaviour, IPointerDownHandler
{
	private const int CELL_SIZE = 40;

	// shortcuts
	ScrollRect m_scrollview;
	ViewManager m_viewMgr;
	StageDataManager m_dataMgr;

	void Start()
	{
		m_scrollview = GameObject.Find ("GameScrollView").GetComponent<ScrollRect> ();
		m_viewMgr = m_scrollview.GetComponent<ViewManager> ();
		m_dataMgr = GameObject.Find ("StageData").GetComponent<StageDataManager> ();
	}

	public void OnPointerDown(PointerEventData eventData)
	{
		//Debug.Log ("mouse click: pos[" + eventData.position.x + ", " + eventData.position.y + "], type[" + eventData.pointerId + "]");
		if (eventData.button == PointerEventData.InputButton.Right) // right btn clicked
			OnRBtnDown (eventData);
		else if (eventData.button == PointerEventData.InputButton.Left)			
			OnLBtnDown (eventData);
	}

	private void OnRBtnDown(PointerEventData eventData)
	{
		Debug.Log ("right clicked");
		int objIndex = m_dataMgr.CreateObject (eventData.position);

		string panelName = "Panel_" + objIndex.ToString ();
		GameObject newPanel = new GameObject (panelName);
		CellPosAmender cellPosAmender = newPanel.AddComponent<CellPosAmender> ();
		cellPosAmender.m_index = objIndex;

		Image image = newPanel.AddComponent<Image> ();
		image.rectTransform.sizeDelta = new Vector2 (CELL_SIZE, CELL_SIZE);
		image.color = Color.white;

		newPanel.transform.SetParent (m_scrollview.transform, false);
		newPanel.transform.position = eventData.position;

		m_viewMgr.SetActivatePanel (newPanel);
	}

	private void OnLBtnDown(PointerEventData eventData)
	{
		Debug.Log ("left clicked");
	}
}
