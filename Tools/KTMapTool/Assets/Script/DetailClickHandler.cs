using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class DetailClickHandler : MonoBehaviour, IPointerClickHandler
{
    // ui shortcuts

    // public
    public void OnPointerClick(PointerEventData eventData)
    {
        StageDataManager.GetInstance().LoadDetailInfo(gameObject);
    }       
}
